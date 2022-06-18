#include <iostream>
#include <string>
#define LOGOUT(msg) std::cout << msg << '\n'


int main(int argc, const char* argv[]) {
    
    if (argc == 2) {
        std::string type = std::string(argv[1]);

        if (type == "--opengl") {
#define MI_ENGINE_OPENGL_BUILD
        }
        else if (type == "--vulkan") {
#define MI_ENGINE_VULKAN_BUILD
        }
        else if (type == "--metal") {
#define MI_ENGINE_METAL_BUILD
        }
    }
    else throw std::runtime_error("You need to specify the build type: i.e.\n--opengl\n--vulkan\n--metal");


#if defined(MI_ENGINE_OPENGL)

    

#endif
}