FROM debian:bullseye-slim

ENV DEBIAN_FRONTEND=noninteractive
ENV PORT=7681

WORKDIR /app

RUN set -e; \
    for i in 1 2 3; do \
        apt-get update && \
        apt-get install -y --fix-missing \
            build-essential \
            libreadline-dev \
            wget \
            curl \
            git \
            ca-certificates \
            ncurses-dev \
            rlwrap \
            cmake \
        && break || echo "Retrying apt-get ($i)..."; \
    done; \
    rm -rf /var/lib/apt/lists/*

RUN wget https://github.com/tsl0922/ttyd/releases/download/1.7.3/ttyd.x86_64 -O /usr/local/bin/ttyd && \
    chmod +x /usr/local/bin/ttyd

COPY . /app

RUN make -C libft

RUN make

EXPOSE 7681

CMD ["ttyd", "-p", "7681", "./minishell"]