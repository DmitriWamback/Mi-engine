:: includes
GLFW_INC=
GLEW_INC=

:: libraries
GLFW_LIB=src/vendor/WIND/glfw
GLEW_LIB=src/vendor/WIND/glew
SNDFILE_LIB=src/vendor/WIND/sndfile

RS_LIB=src/MiLibraries
START_CMD="-L ${RS_LIB} "
CMD="${START_CMD}"

for dir in $RS_LIB/*; do (
    CMD="${CMD} ${dir}"
)

g++ -arch x86_64 -I $GLFW_INC \
                -L $GLFW_LIB $GLFW_LIB/glfw3.dll \
                $GLFW_LIB/libglfw3.a $GLFW_LIB/libglfw3dll.a \
                -I $GLEW_INC \
                -L $GLEW_LIB $GLEW_LIB/glew32.lib $GLEW_LIB/glew32s.lib \
                -L $SNDFILE_LIB $SNDFILE_LIB/libsndfile-1.lib \
                -I src/vendor/includes \
                -I src/shared \
                $CMD \
                src/main.cpp

./a.out