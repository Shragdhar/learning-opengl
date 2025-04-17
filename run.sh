#!/bin/bash

debug_flag="-DDEBUG_TEST=OFF"

# Colors
Color_Off='\033[0m'
Yellow='\033[0;33m'
Green='\033[0;32m'
Cyan='\033[0;36m'
Blue='\033[0;34m'
Red='\033[0;31m'

if [ "$1" == "--debug-test" ]; then
    debug_flag="-DDEBUG_TEST=ON"
fi

if [ -d "build" ]; then
    cd build
else
    echo "-- build directory wasn't found...generating one \n\n"
    mkdir build
    cd build
fi

SECONDS=0
cmake .. $debug_flag
cmake --build .
duration=$SECONDS

echo -e "${Yellow}Time Taken: ${Green}$((duration / 60))m $((duration % 60))s ${Color_Off}"

if [ $? -eq 0 ]; then
    ./main
else
    echo "Build failed. Not running ./main."
fi
