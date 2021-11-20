GLFW_INC=
GLFW_LIB=
GLEW_INC=
GLEW_LIB=

RS_LIB=libs

# create Rust lib
# cargo run --manifest-path src/engine/extern/rs/modelLoader/Cargo.toml --release
# (Change crate type in the Cargo.toml depending on the OS)
# Wind: "crate-type = ["clib"]"
# MacOS: "crate-type = ["cdylib"]"

# macOS
g++ -arch x86_64 -framework OpenGL -I $GLFW_INC \
                -L $GLFW_LIB $GLFW_LIB/libglfw.dylib \
                $GLFW_LIB/libglfw.3.3.dylib $GLFW_LIB/libglfw.3.dylib \
                -I $GLEW_INC \
                -L $GLEW_LIB $GLEW_LIB/libGLEW.2.2.0.dylib $GLEW_LIB/libGLEW.2.2.dylib $GLEW_LIB/libGLEW.a $GLEW_LIB/libGLEW.dylib \
                #-L $RS_LIB $RS_LIB/libmi_model_loader.dylib \
                src/main.cpp

# Wind
g++ -arch x86_64 -I $GLFW_INC \
                -L $GLFW_LIB $GLFW_LIB/libglfw.lib \
                $GLFW_LIB/libglfw.3.3.lib $GLFW_LIB/libglfw.3.lib \
                -I $GLEW_INC \
                -L $GLEW_LIB $GLEW_LIB/libGLEW.2.2.0.lib $GLEW_LIB/libGLEW.2.2.lib $GLEW_LIB/libGLEW.a $GLEW_LIB/libGLEW.lib \
                #-L $RS_LIB $RS_LIB/libmi_model_loader.lib \
                src/main.cpp

./a.out