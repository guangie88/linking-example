# CFFI Example

This set-up demonstrates how Python script can dynamic load from dynamically
linked library, and switch libraries without changing the Python script to call
different implementations of Fibonacci nth solution.

## How to try

You will need to have Python 3 and GCC installed. For Debian / Ubuntu, this
typically means you need to install the following from `apt`:

- python3
- gcc
- golang
- libc-dev

If you prefer to use a Docker set-up, you can run an interactive bash shell with
all the above dependencies:

```bash
docker build . -t linking-example-cffi && \
docker run --rm -it --name linking-example-cffi linking-example-cffi
```

## Dynamic Loading (Part 1)

This section explores the idea of performing dynamic loading from Python script
to call into C-based shared library.

This is the most dynamic way to call an external executable (shared library),
but also the most haphazard way to do so, which should be avoided as much as
possible in practical scenarios.

### `fib_rec.c`

This C code uses the dumbest recursive approach to solve for the Fibonacci
problem.

Run the following to generate the shared library and timing:

```bash
cc -fPIC -shared -o lib/libfib.so fib_rec.c
time ./main_dynload.py 46
```

You should see output that looks like the following:

```bash
fib(46): 1836311903

real    0m15.868s
user    0m15.832s
sys     0m0.020s
```

### `fib_smart.c`

This C code uses Fibonacci closed form and rounding to quickly get the nth
value.

Run the following to generate the shared library and timing:

```bash
cc -fPIC -shared -o lib/libfib.so -lm fib_smart.c  # -lm links to libm.so
time ./main_dynload.py 46
```

You should see output that looks like the following:

```bash
fib(46): 1836311903

real    0m0.049s
user    0m0.037s
sys     0m0.012s
```

### Repeat dynamic loading but for C

C can use `dlopen`, `dlsym` and `dlclose` to perform the same thing as seen in
the above Python script run.

First we need to compile and link `main_dynload.c` to generate an executable
`main`. Note that we need to link against `libdl.so` in order to use the
`dlopen` symbol as seen above.

```bash
cc main_dynload.c -ldl -o main
```

Before running the generated `main` program, run the following to check the
linking in `main`:

```bash
ldd main
```

You should see something like this:

```bash
        linux-vdso.so.1 (0x00007ffd564b8000)
        libdl.so.2 => /lib/x86_64-linux-gnu/libdl.so.2 (0x00007f0a373fd000)
        libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f0a3723c000)
        /lib64/ld-linux-x86-64.so.2 (0x00007f0a3740c000)
```

Note that `libfib.so` is not listed as part of the linking relationship, despite
the source code dynamically loading the shared library.

Now run the program like this:

```bash
cc -fPIC -shared -o lib/libfib.so fib_rec.c
time ./main 46
```

```bash
cc -fPIC -shared -o lib/libfib.so -lm fib_smart.c  # -lm links to libm.so
time ./main 46
```

Both the outputs should be similar to the Python counterparts.

## Dynamic Linking (Part 2)

This section explores the idea of performing dynamic linking during link-time
and is only applicable to compilable (and link-able) source code, such as Go and
C.

First perform the step in [`fib_smart.c`](#fib_smart.c) first to call into
C-based shared library.

Note that actually we can also opt to use the shared library created by step
[`fib_rec.c`](#fib_rec.c).

### Go-based FFI via Dynamic Linking

Simply run

```bash
go build main.go
```

to build the Go main.

To check the dynamic linking performed on the generated `main` executable, run

```bash
ldd main
```

You should see something like this:

```bash
        linux-vdso.so.1 (0x00007ffe86bfb000)
        libfib.so => /app/./lib/libfib.so (0x00007fe927c87000)
        libpthread.so.0 => /lib/x86_64-linux-gnu/libpthread.so.0 (0x00007fe927c63000)
        libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007fe927aa2000)
        libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x00007fe92791f000)
        /lib64/ld-linux-x86-64.so.2 (0x00007fe927c8e000)
```

Note that `main` is now shown to be dependent on our created `libfib.so` shared
library.

Simply run

```bash
./main 10
```

to run and see the effect.

### C Dynamic Linking

Simply run

```bash
cc main.c -Llib -lfib -Wl,-rpath='$ORIGIN/lib' -o main
```

Similarly, run below command to check the dynamic linking on the main program:

```bash
ldd main
```

You should see something like this:

```bash
        linux-vdso.so.1 (0x00007ffc857ef000)
        libfib.so => /app/./lib/libfib.so (0x00007f7b95ce9000)
        libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f7b95b25000)
        libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x00007f7b959a2000)
        /lib64/ld-linux-x86-64.so.2 (0x00007f7b95cf5000)
```

Simply run

```bash
./main 10
```

to run and see the effect.

## Static Linking (Part 3)

This section explores the idea of performing static linking during link-time
and is only applicable to compilable (and link-able) source code, such as Go and
C.

There is no need to build the shared library in either
[`fib_smart.c`](#fib_smart.c) or [`fib_rec.c`](#fib_rec.c).

### C Static Linking

Simply run

```bash
cc main.c fib_smart.c -lm -static -o main
```

to build and statically link against `fib_smart` object (and `libm.a`) to get
a pure statically linked `main`.

Now to check the dynamic linking in the program, run this:

```bash
ldd main
```

You should see:

```bash
        not a dynamic executable
```

Which is correct, because we have just statically linked the `main` program, so
all the symbol implementations will be subsumed into this single executable.

Simply run

```bash
./main 10
```

to run and see the effect.

If you are running in Docker container, you may perform the next few steps to
show that the executable is indeed statically linked and portable across other
Linux distros.

Do not terminate the current Docker session. Open another terminal, and run the
following in your host shell:

```bash
docker cp linking-example-cffi:/app/main ./
./main 10
```

You can try running this same executable in two other Linux distros:

#### Statically linked executable in Alpine

```bash
docker run --rm -it -v "$(pwd)/main:/main" alpine:3.10
./main 10  # In the Docker shell
```

#### Statically linked executable in super old CentOS

```bash
docker run --rm -it -v "$(pwd)/main:/main" centos:5
./main 10  # In the Docker shell
```
