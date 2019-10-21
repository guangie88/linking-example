# CFFI Example

This set-up demonstrates how Python script can dynamic load from dynamically
linked library, and switch libraries without changing the Python script to call
different implementations of Fibonacci nth solution.

## How to try

You will need to have Python 3 and GCC installed. For Debian / Ubuntu, this
typically means you need to install the following from `apt`:

- python3
- gcc
- libc-dev

If you prefer to use a Docker set-up, you can run an interactive bash shell with
all the above dependencies:

```bash
docker build . -t linking-example-cffi && docker run --rm -it linking-example-cffi
```

## Benchmarks

### `fib_rec.c`

This C code uses the dumbest recursive approach to solve for the Fibonacci
problem.

Run the following to generate the shared library and timing:

```bash
cc -fPIC -shared -o lib/libfib.so fib_rec.c
time ./main.py 46
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
cc -fPIC -shared -o lib/libfib.so fib_smart.c
time ./main.py 46
```

You should see output that looks like the following:

```bash
fib(46): 1836311903

real    0m0.049s
user    0m0.037s
sys     0m0.012s
