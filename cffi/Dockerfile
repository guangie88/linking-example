FROM python:3.7-slim

SHELL ["/bin/bash", "-c"]
WORKDIR /app

RUN set -euo pipefail && \
    apt-get update; \
    apt-get install -y --no-install-recommends gcc golang libc-dev neovim; \
    rm -rf /var/lib/apt/lists/*; \
    :

RUN mkdir -p ./lib
COPY *.c *.go *.py ./

ENTRYPOINT ["bash"]
