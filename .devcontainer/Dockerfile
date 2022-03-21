# See here for image contents: https://github.com/microsoft/vscode-dev-containers/tree/v0.209.6/containers/cpp/.devcontainer/base.Dockerfile

# [Choice] Debian / Ubuntu version (use Debian 11/9, Ubuntu 18.04/21.04 on local arm64/Apple Silicon): debian-11, debian-10, debian-9, ubuntu-21.04, ubuntu-20.04, ubuntu-18.04
ARG VARIANT="bullseye"
FROM mcr.microsoft.com/vscode/devcontainers/cpp:0-${VARIANT}

# [Optional] Uncomment this section to install additional packages.
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
     && apt-get -y install --no-install-recommends \
        librdkafka-dev libcrypto++-dev libgtest-dev libjsoncpp-dev \
        libkrb5-dev libuv1-dev \
        libssl-dev \
        zlib1g-dev

RUN  cd /tmp && git clone https://github.com/datastax/cpp-driver.git \
     && cd cpp-driver && mkdir build && cd build \
     && cmake .. && make && make install && cd ..

# for Cassandra's DataStax driver: libkrb5-dev libuv1-dev libssl-dev zlib1g-dev 
#RUN apt-get install -y cassandra-cpp-driver_2.16.0

#RUN apt-get install -y cassandra-cpp-driver-dev
#libuv1-dev libcassandra-cpp-driver-devel cassandra-cpp-driver-debuginfo
#COPY /Users/igorla/dockers/cassandra-cpp-driver_2.16.0-1_amd64.deb /workspaces/KeepId-TheKeep/
# COPY /libs/cassandra-cpp-driver_2.16.0-1_amd64.deb .
#RUN cd /tmp && dpkg -i cassandra-cpp-driver_2.16.0-1_amd64.deb