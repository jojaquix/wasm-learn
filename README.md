# wasm-learn

## Overview
This project is a small playground for learning how to compile C++ to WebAssembly with the Emscripten SDK.

## Prerequisites
- Emscripten SDK (emsdk) installed on your machine
- CMake available on the command line

If your emsdk lives in a different folder than C:\bin\emsdk, adjust the paths below accordingly.

## Prepare the Environment
Open a fresh terminal and load the Emscripten environment before building or running the project.

### PowerShell
`
Set-ExecutionPolicy -Scope Process Bypass -Force
& "C:\bin\emsdk\emsdk_env.ps1"
`

### Command Prompt
`
C:\bin\emsdk\emsdk_env.bat
`

## Build
Configure with CMake (through emcmake) and build the project:
`
emcmake cmake -S . -B build
cmake --build build -j
`

## Run
Launch the development server from within the build\\dist directory using emrun:
`
cd build\dist
emrun --no_browser --port 8080 .
`

With --no_browser, open your browser and navigate to http://localhost:8080 to view the sample.