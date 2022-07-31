# MacOS build

# INSTRUCTIONS
# brew install lua
# cd scripting/luacpp
# mkdir build
# cd build
# cmake ../Source
# make -k `nproc`
# make install
# sh main/scripting-test/run.sh

g++ --std=c++17 main/scripting-test/main.cpp -I /usr/local/include/LuaCpp -I /usr/local/include/lua5.4 -lluacpp -o scripting-test.out