cd build
cmake .. -G "Ninja"
cmake --build .
echo "\n------------------ RUNNING ------------------\n"
./$1
echo "\n------------------ END ------------------\n"