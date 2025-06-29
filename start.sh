#!/bin/bash

set -e

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

mkdir -p build

echo -e "${GREEN}Compiling file generator...${NC}"
c++ -std=c++17 -O3 -o build/file_generator src/main.cpp

if [ $? -eq 0 ]; then
    echo -e "${GREEN}Compilation successful! Running the program...${NC}\n"

    ./build/file_generator

    read -p "Clean up build files? (y/n): " -n 1 -r
    echo
    if [[ $REPLY =~ ^[Yy]$ ]]; then
        rm -rf build
        echo "Build files cleaned up."
    fi
else
    echo -e "${RED}Compilation failed. Please check the error messages above.${NC}"
    exit 1
fi
