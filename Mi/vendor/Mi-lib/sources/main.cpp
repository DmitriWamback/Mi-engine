#include <iostream>

extern "C" {
    float*      MitiParse(const char* data, int* size);
    void        MitiFindDType(const char* data);
    const char* GLSLImport(const char* glslSource, const char* path);
    void        Pointer(int* t);
}

int main() {

    const char* GLVSRC = GLSLImport("#version 330 core\n"
                                    "#INCLUDE \"../test/hello.glsl\"\n"
                                    "#INCLUDE \"../test/test1.glsl\"",
                                    "glsl/main/main.glsl");

    //std::cout << GLVSRC << '\n';
    int t;
    Pointer(&t);
    std::cout << t << '\n';
}