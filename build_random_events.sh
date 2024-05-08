mkdir -p build && cd build
cmake .. -DCMAKE_INSTALL_PREFIX=../release -DCMAKE_BUILD_TYPE=Release
make -j8
#make install
