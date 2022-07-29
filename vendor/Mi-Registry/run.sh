FREE_TYPE=$(freetype-config --libs)
g++ main.cpp -I vendor/include $FREE_TYPE && ./a.out