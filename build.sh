#!/bin/bash
# Dodoi-lab - Research and Development Laboratory
# PS2 Game Development Build Script for macOS/Linux
#
# @author Hudson Schumaker
#
# Copyright (c) 2025 dodoi-lab. All rights reserved.
#
# This software is provided 'as-is', without any express or implied
# warranty. In no event will the authors be held liable for any damages
# arising from the use of this software.
#

set -e

show_help() {
    echo "PS2 Game Development Build Script"
    echo ""
    echo "Usage: ./build.sh [command]"
    echo ""
    echo "Commands:"
    echo "  build    - Build the Docker image"
    echo "  compile  - Compile the PS2 game"
    echo "  iso      - Compile and create ISO file"
    echo "  shell    - Open interactive shell in container"
    echo "  clean    - Clean build artifacts"
    echo "  run      - Clean, compile, and create ISO"
    echo "  help     - Show this help message"
    echo ""
}

build_docker() {
    echo "Building PS2 development Docker image..."
    docker build -t ps2-sdk .
    echo "Docker image built successfully!"
}

compile_game() {
    echo "Compiling PS2 game..."
    docker run --rm -v "$(pwd):/usr/src/ps2game" -w /usr/src/ps2game ps2-sdk make
    echo "Compilation successful! Check bin/ folder for ps2game.elf"
}

create_iso() {
    echo "Creating PS2 ISO..."
    docker run --rm -v "$(pwd):/usr/src/ps2game" -w /usr/src/ps2game ps2-sdk make iso
    echo "ISO created successfully! Check bin/ folder for ps2game.iso"
}

open_shell() {
    echo "Opening interactive shell in PS2 development container..."
    docker run --rm -it -v "$(pwd):/usr/src/ps2game" -w /usr/src/ps2game ps2-sdk /bin/sh
}

clean_artifacts() {
    echo "Cleaning build artifacts..."
    docker run --rm -v "$(pwd):/usr/src/ps2game" -w /usr/src/ps2game ps2-sdk make clean
    docker run --rm -v "$(pwd):/usr/src/ps2game" -w /usr/src/ps2game ps2-sdk make clean-iso
    echo "Build artifacts cleaned!"
}

run_all() {
    clean_artifacts
    compile_game
    create_iso
}

# Main script logic
case "${1:-help}" in
    "build")
        build_docker
        ;;
    "compile")
        compile_game
        ;;
    "iso")
        create_iso
        ;;
    "shell")
        open_shell
        ;;
    "clean")
        clean_artifacts
        ;;
    "run")
        run_all
        ;;
    "help"|*)
        show_help
        ;;
esac
