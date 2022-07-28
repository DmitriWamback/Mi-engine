g++ -L $(pwd)/exported \
       $(pwd)/exported/libmain.a \
       sources/main.cpp -o package/result
       
./package/result