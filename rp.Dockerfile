# Use a specific Ubuntu LTS version for stability
FROM arm32v7/ubuntu:20.04

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

COPY /build /app
# You might want to set a working directory if needed
 WORKDIR /app

# Specify the command to run when the container starts
 CMD ["./ClientMain"]
