FROM python:3.7-slim

SHELL ["/bin/bash", "-c"]
WORKDIR /app

RUN set -euo pipefail && \
    apt-get update; \
    apt-get install -y --no-install-recommends gcc libc-dev; \
    rm -rf /var/lib/apt/lists/*; \
    :

RUN mkdir -p ./lib
COPY *.c main.py ./

ENTRYPOINT ["bash"]
