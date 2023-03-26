# Use the official Ubuntu image as the base
FROM ubuntu:20.04

# Update the package list and install build tools
RUN apt-get update && \
    apt-get install -y clang build-essential

# Set the working directory
WORKDIR /app

# Copy the source code and Makefile into the container
COPY . /app

# Build the C program using the Makefile
RUN make

# Run the program
CMD ["./advcalc"]