# uses LF only
echo "Starting the cmake build script for the Keep (debug version)."
cmake -S . -B build -D CMAKE_CXX_COMPILER=clang++ -D CMAKE_BUILD_TYPE=Debug
echo "Making the project.."
cd build
make
