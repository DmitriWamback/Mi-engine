# includes
INCLUDES=src/vendor/OSX/include

# libraries
GLFW_LIB=src/vendor/OSX/glfw
GLEW_LIB=src/vendor/OSX/glew
SNDFILE_LIB=src/vendor/OSX/sndfile

RS_LIB=src/MiLibraries

# getting directories for RS_LIB
START_CMD="-L ${RS_LIB} "
CMD="${START_CMD}"

for dir in $RS_LIB/*; do
    CMD="${CMD} ${dir}"
done

g++ -arch x86_64 -framework OpenGL -framework OpenAL -I $INCLUDES \
                -L $GLFW_LIB $GLFW_LIB/libglfw.dylib \
                $GLFW_LIB/libglfw.3.3.dylib $GLFW_LIB/libglfw.3.dylib \
                -L $GLEW_LIB $GLEW_LIB/libGLEW.2.2.0.dylib $GLEW_LIB/libGLEW.2.2.dylib $GLEW_LIB/libGLEW.a $GLEW_LIB/libGLEW.dylib \
                -L $SNDFILE_LIB $SNDFILE_LIB/scUBlibsndfile.a \
                -I src/vendor/include \
                $CMD \
                src/opengl/main.cpp
./a.out