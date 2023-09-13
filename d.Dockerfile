 Use an official Ubuntu as a parent image
FROM ubuntu:latest

# Set the working directory inside the container
WORKDIR /app

# Install necessary dependencies
RUN apt-get update && apt-get install -y \
    cmake \
    build-essential \
    libopencv-dev \
    libgrpc++-dev \
    protobuf-compiler \
    # Add other dependencies as needed

# Copy your project files into the container
COPY . .

# Compile the protobuf file
RUN mkdir build && cd build && cmake ..
RUN cd proto && protoc --cpp_out=. camera_service.proto

# Build your CMake project
RUN cd build && make

# Set the entry point for your application
CMD ["./ServerMain"]  # Change this to the appropriate binary name
