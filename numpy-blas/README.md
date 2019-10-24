# NumPy with different BLAS implementations

This whole set-up is Dockerized for simplicity. To proceed, you will need
`docker` command.

To build and run the set-up, run the following:

```bash
docker build . -t linking-example-numpy-blas && docker run --rm -it linking-example-numpy-blas
```

Once completed, you will enter into a new shell that is inside the running
Docker container.

## Environments

### NumPy with Intel MKL

To activate the `virtualenv` environment:

```bash
source numpy-mkl/bin/activate
```

To check symbol to perform computation of eigenvalues for integers `cgeev`.

```bash
nm numpy-mkl/lib/libmkl_rt.so | grep cgeev
```

### NumPy with OpenBLAS

To activate the `virtualenv` environment:

```bash
source numpy-openblas/bin/activate
```

To check symbol to perform computation of eigenvalues for integers `cgeev`.

```bash
nm numpy-openblas/lib/python3.6/site-packages/numpy/.libs/libopenblas*.so | grep cgeev
```

## Show configuration and linked BLAS library

The following are common steps once the above environment is activated.

To show the whether OpenBLAS or Intel MKL libraries are used:

```bash
python -c "import numpy; numpy.__config__.show()"
```

## Benchmark command

```bash
time python -c "import numpy as np; n = 2048; P = np.random.randint(0,10,(n,n)); np.linalg.eig(P @ P.T)"
```

### Intel MKL benchmark example

```bash
real    0m13.071s
user    0m18.606s
sys     0m0.208s
```

### OpenBLAS benchmark example

```bash
real    0m17.106s
user    0m32.353s
sys     0m11.128s
```

`real` time is the wall clock time duration that we are interested in.

Compared against the Intel MKL's benchmark, NumPy with Intel MKL is generally
around 30-40% faster for square matrix P x P(T) of integers, with size of 2048.

## Deactivation

Simply run while the environment is being activated:

```bash
deactivate
```
