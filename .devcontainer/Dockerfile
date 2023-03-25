# See here for image contents: https://github.com/microsoft/vscode-dev-containers/tree/v0.209.6/containers/cpp/.devcontainer/base.Dockerfile

# [Choice] Debian / Ubuntu version (use Debian 11/9, Ubuntu 18.04/21.04 on local arm64/Apple Silicon): debian-11, debian-10, debian-9, ubuntu-21.04, ubuntu-20.04, ubuntu-18.04
ARG VARIANT="bullseye"
FROM mcr.microsoft.com/vscode/devcontainers/cpp:0-${VARIANT}

# [Optional] Uncomment this section to install additional packages.
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
     && apt-get -y install --no-install-recommends \
        # librdkafka-dev \
        libcrypto++-dev libgtest-dev libjsoncpp-dev \
        libkrb5-dev libuv1-dev \
        libssl-dev \
        zlib1g-dev

# installation of DataStax's cpp-driver Cassandra library
RUN  cd /tmp && git clone https://github.com/datastax/cpp-driver.git \
     && cd cpp-driver && mkdir build && cd build \
     && cmake .. && make && make install && cd ..

# download source and compilation of librdkafka Kafka library -b v2.0.2 (compatible with modern-cpp-kafka v2023.03.07)
RUN  cd /tmp && git clone https://github.com/confluentinc/librdkafka.git -b v2.0.2 \
     && cd /tmp/librdkafka && ./configure --install-deps && make && sudo make install

# installation of modern-cpp-kafka Kafka header-only library -b v2023.03.07 (compatible with librdkafka v2.0.2)
RUN  cd /tmp && git clone https://github.com/morganstanley/modern-cpp-kafka.git -b v2023.03.07 \
     && cd /tmp/modern-cpp-kafka/include && cp -r kafka /usr/local/include

# installation of Combat-Spdlog header-only library
RUN  cd /tmp && git clone https://github.com/gabime/spdlog.git \
     && cd /tmp/spdlog/include && cp -r spdlog /usr/local/include

# Attempt to move the Docker container to EST time zone 
#RUN echo "America/New_York" > /etc/timezone
#RUN dpkg-reconfigure -f noninteractive tzdata  