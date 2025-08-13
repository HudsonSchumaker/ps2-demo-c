# Dodoi-lab - Research and Development Laboratory
# PS2 Game Development Dockerfile
# Uses the official PS2Dev Docker image for compilation
#
# @author Hudson Schumaker
# @email hudson.schumaker@me.com
#
# Copyright (c) 2025 dodoi-lab. All rights reserved.
#
# This software is provided 'as-is', without any express or implied
# warranty. In no event will the authors be held liable for any damages
# arising from the use of this software.
#

FROM ps2dev/ps2dev:latest

# Install make and required math libraries
RUN apk add --no-cache \
    make \
    mpc1-dev \
    mpfr-dev \
    gmp-dev \
    cdrkit

# Set working directory
WORKDIR /usr/src/ps2game

# Set up build environment
ENV PS2DEV=/usr/local/ps2dev
ENV PS2SDK=$PS2DEV/ps2sdk
ENV GSKIT=$PS2DEV/gsKit
ENV PATH=$PATH:$PS2DEV/bin:$PS2DEV/ee/bin:$PS2DEV/iop/bin

# Copy project files
COPY . .

# Create build directories
RUN mkdir -p build bin dvdrom

# Default command is to build the game
CMD ["make"]
