#!/bin/bash

# Clean up
rm -rf build

# Build the project
mkdir build
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build