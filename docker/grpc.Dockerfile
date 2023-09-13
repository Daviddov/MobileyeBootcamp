FROM ubuntu:20.04

ARG GPRC_VERSION=1.34.0
ARG NUM_JOBS=8

ENV DEBIAN_FRONTEND noninteractive

# Install package dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
        build-essential \
        software-properties-common \
        autoconf \
        automake \
        libtool \
        pkg-config \
        ca-certificates \
        wget \
        git \
        curl \
        vim \
        gdb \
        valgrind \
        cmake \
        libopencv-dev

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

RUN apt install build-essential cmake libgtk2.0-dev pkg-config \
    libavcodec-dev libavformat-dev libswscale-dev -y && \
    git clone https://github.com/opencv/opencv.git && \
    cd opencv && mkdir build && cd build && \
    cmake -D CMAKE_BUILD_TYPE=Release -D BUILD_SHARED_LIBS=NO .. && \
    cat /proc/cpuinfo | grep "processor" | wc -l | xargs make -j && \
    make install && cd ../.. && \
    rm -rf opencv

RUN apt-get clean