# NumPy with different BLAS implementations

You will need `conda` command to run the following commands.

## Environments

### NumPy with Intel MKL

```bash
conda env create -f numpy-mkl.yml
conda activate numpy-mkl
```

To check symbol to perform computation of eigenvalues for integers `cgeev`.

```bash
nm /home/guangie/.conda/envs/numpy-mkl/lib/libmkl_rt.so | grep cgeev
```

### NumPy with OpenBLAS

```bash
conda env create -f numpy-openblas.yml
conda activate numpy-openblas
```

To check symbol to perform computation of eigenvalues for integers `cgeev`.

```bash
nm ~/.conda/envs/numpy-openblas/lib/libopenblas.so | grep cgeev
```

## Show configuration and linked BLAS library

```bash
python -c "import numpy; numpy.__config__.show()"
```

## Benchmark command

```bash
time python -c "import numpy as np; n = 2048; P = np.random.randint(0,10,(n,n)); np.linalg.eig(P @ P.T)"
```

## Alternative benchmark command

You will need the `hyperfine` benchmarking command, whose releases can be found
here: <https://github.com/sharkdp/hyperfine/releases>.

```bash
hyperfine 'python -c "import numpy as np; n = 1024; P = np.random.randint(0,10,(n,n)); np.linalg.eig(P @ P.T)"'
```
