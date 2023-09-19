# Use the appropriate base image for Raspberry Pi 3 (32-bit)
FROM arm32v7/ubuntu:20.04

# Define environment variables
ARG GPRC_VERSION=1.34.0
ARG NUM_JOBS=8
ENV DEBIAN_FRONTEND noninteractive
ENV MY_INSTALL_DIR=/usr/local

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
    libopencv-dev \
    libavcodec-dev \
    libavformat-dev \
    libswscale-dev \
    libgtk2.0-dev

# Install gRPC
RUN git clone --recurse-submodules -b v${GPRC_VERSION} https://github.com/grpc/grpc /tmp/grpc && \
    cd /tmp/grpc && \
    mkdir -p cmake/build && \
    cd cmake/build && \
    cmake -DgRPC_INSTALL=ON \
        -DgRPC_BUILD_TESTS=OFF \
        -DCMAKE_INSTALL_PREFIX=$MY_INSTALL_DIR \
        ../.. && \
    make -j${NUM_JOBS} && \
    make install && \
    cd / && \
    rm -rf /tmp/grpc

# Install OpenCV
RUN git clone https://github.com/opencv/opencv.git /tmp/opencv && \
    cd /tmp/opencv && \
    mkdir build && \
    cd build && \
    cmake -D CMAKE_BUILD_TYPE=Release -D BUILD_SHARED_LIBS=NO .. && \
    make -j$(nproc) && \
    make install && \
    cd / && \
    rm -rf /tmp/opencv

# Clean up
RUN apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# Create a working directory
WORKDIR /mnt/build/

# Define the default command
CMD ["./ClientMain"]
