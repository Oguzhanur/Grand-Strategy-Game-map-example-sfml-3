mkdir
cmake -B build
make -C build
cp -r ./source/ ./build/bin/
./build/bin/main