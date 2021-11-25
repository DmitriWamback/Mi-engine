GLFW_INC=
GLFW_LIB=
GLEW_INC=
GLEW_LIB=

RS_LIB=libs

g++ -arch x86_64 -I $GLFW_INC \
                -L $GLFW_LIB $GLFW_LIB/libglfw.lib \
                $GLFW_LIB/libglfw.3.3.lib $GLFW_LIB/libglfw.3.lib \
                -I $GLEW_INC \
                -L $GLEW_LIB $GLEW_LIB/libGLEW.2.2.0.lib $GLEW_LIB/libGLEW.2.2.lib $GLEW_LIB/libGLEW.a $GLEW_LIB/libGLEW.lib \
                ::-L $RS_LIB $RS_LIB/libmi_model_loader.lib \
                src/main.cpp

./a.out