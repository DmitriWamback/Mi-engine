# includes
GLFW_INC=
GLEW_INC=

# libraries
GLFW_LIB=src/vendor/OSX/glfw
GLEW_LIB=src/vendor/OSX/glew
SNDFILE_LIB=src/vendor/OSX/sndfile

RS_LIB=src/MiLibs

g++ -arch x86_64 -framework OpenGL -framework OpenAL -I $GLFW_INC \
                -L $GLFW_LIB $GLFW_LIB/libglfw.dylib \
                $GLFW_LIB/libglfw.3.3.dylib $GLFW_LIB/libglfw.3.dylib \
                -I $GLEW_INC \
                -L $GLEW_LIB $GLEW_LIB/libGLEW.2.2.0.dylib $GLEW_LIB/libGLEW.2.2.dylib $GLEW_LIB/libGLEW.a $GLEW_LIB/libGLEW.dylib \
                -L $SNDFILE_LIB $SNDFILE_LIB/scUBlibsndfile.a \
                -L $RS_LIB $RS_LIB/libmi_model_loader.dylib \
                src/main.cpp
./a.out