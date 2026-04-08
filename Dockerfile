FROM debian:bullseye

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    libreadline-dev \
    wget \
    && rm -rf /var/lib/apt/lists/*

RUN apt-get update && apt-get install -y \
    build-essential \
    libreadline-dev \
    wget \
    rlwrap \
    && rm -rf /var/lib/apt/lists/*


RUN wget https://github.com/tsl0922/ttyd/releases/latest/download/ttyd.x86_64 \
    && chmod +x ttyd.x86_64 \
    && mv ttyd.x86_64 /usr/local/bin/ttyd    

WORKDIR /app
COPY . .
    
RUN make
    
EXPOSE 7681
    
# Dockerfile
CMD sh -c "ttyd -t allow_reconnect=true -p ${PORT:-7681} -i 0.0.0.0 rlwrap ./minishell"
