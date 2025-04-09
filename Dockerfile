# Use NVIDIA CUDA base image with Ubuntu 24.04
FROM nvidia/cuda:12.8.1-devel-ubuntu24.04

RUN apt-get update && apt-get install -y \
    clang-format \
    vim \
    build-essential \
    cmake \
    git \
    libboost-all-dev \
    python3 \
    python3-pip \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /opt

RUN git clone https://github.com/alpaka-group/alpaka.git

RUN git clone --branch v2.13.10 https://github.com/catchorg/Catch2.git

RUN git clone https://gitlab.com/libeigen/eigen.git

RUN git clone https://github.com/google/benchmark.git

WORKDIR /workspace

COPY . /workspace

CMD ["/bin/bash"]

