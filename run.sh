if [ -d "build" ]; then
    cd build
else
    echo "-- build directory wasn't found...generating one \n\n"
    mkdir build
    cd build
fi

cmake ..
cmake --build .

if [ $? -eq 0 ]; then
    ./main
else
    echo "Build failed. Not running ./main."
fi