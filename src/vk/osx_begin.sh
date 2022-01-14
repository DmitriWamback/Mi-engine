# includes
INCLUDES=src/vendor/OSX/include

# libraries
GLFW_LIB=src/vendor/OSX/glfw
VK_LIB=src/vendor/OSX/vk
SNDFILE_LIB=src/vendor/OSX/sndfile

RS_LIB=src/MiLibraries

# getting directories for RS_LIB
START_CMD="-L ${RS_LIB} "
CMD="${START_CMD}"

for dir in $RS_LIB/*; do
    CMD="${CMD} ${dir}"
done

g++ -arch x86_64 -framework OpenAL -I $INCLUDES \
                -L $GLFW_LIB $GLFW_LIB/libglfw.dylib \
                $GLFW_LIB/libglfw.3.3.dylib $GLFW_LIB/libglfw.3.dylib \
                -L $VK_LIB $VK_LIB/libvulkan.1.2.198.dylib $VK_LIB/libvulkan.1.dylib \
                -L $SNDFILE_LIB $SNDFILE_LIB/scUBlibsndfile.a \
                -I src/vendor/include \
                $CMD \
                src/vk/main.cpp
./a.out