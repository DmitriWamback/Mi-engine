REGISTRY=vendor/Mi-Registry
FRAMEWORK=$1

INCLUDES_DIRECTORY=vendor/include
GLFW_LIBRARIES_DIRECTORY=vendor/os/mac/glfw
GLEW_LIBRARIES_DIRECTORY=vendor/os/mac/glew

g++ --std=c++17 -framework OpenGL -framework OpenAL -I vendor/glm -I vendor/Mi-Registry \
    -I $INCLUDES_DIRECTORY \
    -L $GLEW_LIBRARIES_DIRECTORY $GLEW_LIBRARIES_DIRECTORY/libGLEW.2.2.0.dylib $GLEW_LIBRARIES_DIRECTORY/libGLEW.2.2.dylib $GLEW_LIBRARIES_DIRECTORY/libGLEW.a $GLEW_LIBRARIES_DIRECTORY/libGLEW.dylib \
    -L $GLFW_LIBRARIES_DIRECTORY $GLFW_LIBRARIES_DIRECTORY/libglfw.3.3.dylib $GLFW_LIBRARIES_DIRECTORY/libglfw.3.dylib $GLFW_LIBRARIES_DIRECTORY/libglfw.dylib \
    main/main.cpp \
    -o BuildOSX.out

./BuildOSX.out