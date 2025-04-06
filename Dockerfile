# Use NVIDIA CUDA base image with Ubuntu 24.04
FROM nvidia/cuda:12.8.1-devel-ubuntu24.04

# Base: Ubuntu 24.04
# FROM ubuntu:24.04

# Install system dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    libboost-all-dev \
    python3 \
    python3-pip \
    && rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /opt

RUN git clone https://github.com/alpaka-group/alpaka.git

# Install Catch2 (full version with CMake config)
# Aggiungi Catch2 (solo header)
RUN git clone --branch v2.13.10 https://github.com/catchorg/Catch2.git

# Set environment variable to use installed Alpaka
# ENV CMAKE_PREFIX_PATH="/usr/local/cmake:$CMAKE_PREFIX_PATH"

# Clone Eigen (header-only, no build)
RUN git clone https://gitlab.com/libeigen/eigen.git

# Print the CMAKE_PREFIX_PATH value
# RUN echo "CMAKE_PREFIX_PATH is set to: $CMAKE_PREFIX_PATH"

# List contents of /usr/local to check if Alpaka is installed
# RUN ls /usr/local

# Set working directory
WORKDIR /workspace

# Copy your project into the container
COPY . /workspace

# Default command (can override when running)
CMD ["/bin/bash"]

