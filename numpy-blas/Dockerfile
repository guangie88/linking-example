FROM python:3.6-slim
SHELL ["/bin/bash", "-c"]

RUN pip install --no-cache-dir virtualenv

WORKDIR /app

RUN set -euo pipefail && \
    python -m venv /app/numpy-openblas; \
    PATH=/app/numpy-openblas/bin pip install --no-cache-dir numpy; \
    :

# Note that Python 3.7 doesn't have intel-numpy at the moment
RUN set -euo pipefail && \
    python -m venv /app/numpy-mkl; \
    PATH=/app/numpy-mkl/bin pip install --no-cache-dir intel-numpy; \
    :

# Install miscellaneous packages
RUN set -euo pipefail && \
    apt-get update; \
    apt-get install -y --no-install-recommends binutils; \
    rm -rf /var/lib/apt/lists/*; \
    :

ENTRYPOINT ["bash"]

# Conda set-up, unable to conda init
# FROM debian:buster-slim
# SHELL ["/bin/bash", "-c"]

# RUN set -euo pipefail && \
#     apt-get update; \
#     apt-get install -y --no-install-recommends curl ca-certificates; \
#     rm -rf /var/lib/apt/lists/*; \
#     :

# ARG MINICONDA3_VERSION=4.7.12
# RUN set -euo pipefail && \
#     curl -fo conda "https://repo.anaconda.com/pkgs/misc/conda-execs/conda-${MINICONDA3_VERSION}-linux-64.exe"; \
#     chmod +x conda; \
#     mv conda /usr/local/bin/; \
#     :

# RUN adduser --gecos "" --disabled-password conda
# USER conda

# WORKDIR /home/conda
# RUN conda init bash
# COPY *.yml ./
