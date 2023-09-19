# Use a minimal Ubuntu image
FROM ubuntu:20.04

# Install the necessary runtime dependencies
RUN apt-get update && apt-get install -y \
    libopencv-core4.2 \
    libopencv-imgcodecs4.2 \
    libavcodec-dev \
    libavformat-dev \
    libswscale-dev \
    libdc1394-22 
    
WORKDIR /mnt/build

CMD ./ClientMain