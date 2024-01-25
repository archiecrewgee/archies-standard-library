cd build
cmake .. -G "Ninja"
cmake --build .
echo "\nRUNNING\n"
./test