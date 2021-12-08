GLFW_INC=
GLFW_LIB=
GLEW_INC=
GLEW_LIB=
SNDFILE_LIB=src/vendor/WIND/sndfile

RS_LIB=src/MiLibs

g++ -arch x86_64 -I $GLFW_INC \
                -L $GLFW_LIB $GLFW_LIB/glfw3.dll \
                $GLFW_LIB/libglfw3.a $GLFW_LIB/libglfw3dll.a \
                -I $GLEW_INC \
                -L $GLEW_LIB $GLEW_LIB/glew32.lib $GLEW_LIB/glew32s.lib \
                -L $SNDFILE_LIB $SNDFILE_LIB/libsndfile-1.lib \
                -L $RS_LIB $RS_LIB/libmi_model_loader.lib \
                src/main.cpp

./a.out