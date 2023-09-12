FROM ubuntu:20.04

LABEL maintainer="David B"

ARG GPRC_VERSION=1.34.0
ARG NUM_JOBS=8

ENV DEBIAN_FRONTEND noninteractive

# Install essential dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    git \
    wget \
    ca-certificates

# Install gRPC dependencies
RUN apt-get install -y \
    autoconf \
    automake \
    libtool \
    pkg-config

# Install OpenCV dependencies
RUN apt-get install -y \
    libopencv-dev \
    libgtk2.0-dev \
    pkg-config \
    libavcodec-dev \
    libavformat-dev \
    libswscale-dev


# gRPC
# https://github.com/grpc/grpc/tree/master/src/cpp
# https://github.com/grpc/grpc/blob/master/BUILDING.md
RUN cd /tmp && \
    apt-get install -y build-essential autoconf libtool pkg-config && \
    git clone --recurse-submodules -b v${GPRC_VERSION} https://github.com/grpc/grpc && \
    cd grpc && \
    mkdir -p cmake/build && \
    cd cmake/build && \
    cmake -DgRPC_INSTALL=ON \
        -DgRPC_BUILD_TESTS=OFF \
        -DCMAKE_INSTALL_PREFIX=$MY_INSTALL_DIR \
        ../.. && \
    make -j${NUM_JOBS} && \
    make install

# Clean up
RUN apt-get clean && \
    rm -rf /var/lib/apt/lists/*
