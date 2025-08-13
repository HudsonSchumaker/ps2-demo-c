:: Dodoi-lab - Research and Development Laboratory
:: PS2 Game Development Build Script for Windows
::
:: @author Hudson Schumaker
:: @email hudson.schumaker@me.com
:: 
:: Copyright (c) 2025 dodoi-lab. All rights reserved.
:: 
:: This software is provided 'as-is', without any express or implied
:: warranty. In no event will the authors be held liable for any damages
:: arising from the use of this software.
::

@echo off
setlocal

if "%1"=="build" goto build
if "%1"=="compile" goto compile
if "%1"=="iso" goto iso
if "%1"=="shell" goto shell
if "%1"=="clean" goto clean
if "%1"=="help" goto help

:help
echo PS2 Game Development Build Script
echo.
echo Usage: build.bat [command]
echo.
echo Commands:
echo   build    - Build the Docker image
echo   compile  - Compile the PS2 game
echo   iso      - Compile and create ISO file
echo   shell    - Open interactive shell in container
echo   clean    - Clean build artifacts
echo   help     - Show this help message
echo.
goto end

:build
echo Building PS2 development Docker image...
docker build -t ps2game .
if %errorlevel% neq 0 (
    echo Failed to build Docker image!
    exit /b 1
)
echo Docker image built successfully!
goto end

:compile
echo Compiling PS2 game...
docker run --rm -v "%cd%:/usr/src/ps2game" -w /usr/src/ps2game ps2game make
if %errorlevel% neq 0 (
    echo Compilation failed!
    exit /b 1
)
echo Compilation successful! Check bin/ folder for ps2game.elf
goto end

:iso
echo Creating PS2 ISO...
docker run --rm -v "%cd%:/usr/src/ps2game" -w /usr/src/ps2game ps2game make iso
if %errorlevel% neq 0 (
    echo ISO creation failed!
    exit /b 1
)
echo ISO created successfully! Check bin/ folder for ps2game.iso
goto end

:shell
echo Opening interactive shell in PS2 development container...
docker run --rm -it -v "%cd%:/usr/src/ps2game" -w /usr/src/ps2game ps2game /bin/sh
goto end

:clean
echo Cleaning build artifacts...
docker run --rm -v "%cd%:/usr/src/ps2game" -w /usr/src/ps2game ps2game make clean
docker run --rm -v "%cd%:/usr/src/ps2game" -w /usr/src/ps2game ps2game make clean-iso
echo Build artifacts cleaned!
goto end

:end
endlocal
