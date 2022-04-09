GLFW_LIB=src/vendor/OSX/glfw
GLEW_LIB=src/vendor/OSX/glew

g++ --std=c++17 -framework OpenGL \
    -L $GLFW_LIB $GLFW_LIB/libglfw.dylib \
    $GLFW_LIB/libglfw.3.3.dylib $GLFW_LIB/libglfw.3.dylib \
    -L $GLEW_LIB $GLEW_LIB/libGLEW.2.2.0.dylib $GLEW_LIB/libGLEW.2.2.dylib $GLEW_LIB/libGLEW.a $GLEW_LIB/libGLEW.dylib \
    src/mit/main.cpp && ./a.out