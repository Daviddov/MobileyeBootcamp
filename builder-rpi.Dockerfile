# Start with an ARM64 Ubuntu image
FROM haiku54/cvclient_base

VOLUME . /mnt
# Set the working directory to /app
WORKDIR /app

# Copy the current directory contents into the container at /app
COPY . /app

# Build the project
RUN cmake -B build  && cmake --build build --config Release --parallel

# Copy the compiled files to a specific directory in the container
#RUN cp -r /app/build /mnt/build/

CMD ./ClientMain