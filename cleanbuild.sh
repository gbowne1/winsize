#!/bin/bash

set -e

CXX=g++  # or clang++
CXXFLAGS="-std=c++17 -Wall -Wextra -O2 -m64"
INCLUDES="-Iinclude"
SOURCES="src/main.cpp src/Console.cpp"
OUTPUT="build/console_app"

mkdir -p build
$CXX $CXXFLAGS $INCLUDES $SOURCES -o $OUTPUT

echo "Build complete: $OUTPUT"
