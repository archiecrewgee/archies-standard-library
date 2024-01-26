# import the ubuntu as base image. Note that 22.04 version was the latest stable release at time of writing 25/01/2024
# this includes gcc of version 11.4.0
FROM ubuntu:22.04

# set as no user interface (pure terminal interaction)
ENV DEBIAN_FRONTEND=non-interactive

# install essential packages
RUN \
    apt update -y && apt upgrade -y && apt install -y \
# Basic tools
    wget \
    python3 \
# Build tools
    cmake \ 
    ninja-build \
# Compilers [note that GCC is included with the base Ubuntu release so does not need to be added here]
    g++ \
    gcc-arm-none-eabi 

# set working directory to top level of linux 
WORKDIR /

# set commands to run from bash
CMD "/bin/bash"