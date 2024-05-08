mkdir -p build

pushd build
cmake .. -DCMAKE_INSTALL_PREFIX=../release -DCMAKE_BUILD_TYPE=Release
make -j8
make install

pushd test
ctest
popd
popd
