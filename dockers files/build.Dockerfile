# Use a specific Ubuntu LTS version for stability
FROM ubuntu:20.04

# Update the package list and install necessary dependencies in a single RUN step
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y \
    libopencv-core4.2 \
    libopencv-imgcodecs4.2 \
    libavcodec-dev \
    libavformat-dev \
    libswscale-dev \
    libdc1394-22 \
    && rm -rf /var/lib/apt/lists/*

# Clean up package cache to reduce image size
RUN apt-get clean

#WORKDIR /mnt/build

#CMD ./ClientMain