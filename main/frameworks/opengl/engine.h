#if defined(_WIN32)
    #if defined(_WIN64)
        #define MI_WINDOW_PLATFORM
    #endif

#elif defined(__APPLE__) || defined(__MACH__)
    #define MI_APPLE_PLATFORM

#elif defined(__linux__)
    #define MI_LINUX_PLATFORM
#endif

#include <iostream>
#include <memory>
#include <functional>
#include <string>
#include <map>
#include <vector>

#define MI_ENGINE_OPENGL
#define LOGOUT(x)      std::cout << x << '\n'
#define MI_ASSERT(msg) throw std::runtime_error(msg)

namespace __mi { namespace __internal {
    bool __mi_GAME_DEVELOPMENT_STAGE = true;
    bool __mi_RELEASE_TITLE_SCREEN   = false;
    float __mi_title_screen_opacity  = 1.0;

    void __mi_compile_and_build_release() {
        if (__mi_GAME_DEVELOPMENT_STAGE) __mi_GAME_DEVELOPMENT_STAGE = false;
    }

    void __mi_play_title_screen() {
        if (!__mi_RELEASE_TITLE_SCREEN && !__mi_GAME_DEVELOPMENT_STAGE) {
            // play title screen
            
            __mi_RELEASE_TITLE_SCREEN = true;
        }
    }
}}

int MI_ENTITY_COUNT = 0;
#define __MI_INCREMENT_ENTITY_COUNT() MI_ENTITY_COUNT++
#define __MI_BUILD_RELEASE __mi::__internal::__mi_compile_and_build_release()

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/vec3.hpp>

namespace Mi { namespace Util {
    GLFWwindow* MicoreMainwindow;
}}

/* Core graphics */
#include "util/rendering/shader.h"
#include "util/frame/texture.h"
#include "util/rendering/material.h"

namespace Mi { namespace Storage {

    std::map<std::string, Mi::Shader> storageShaders;
    std::string sceneName;
}}

namespace Mi {
    float deltaTime;
}

// Mi Registry
//#include <Mi-Attrib/registry.h>
#include <errors.h>
#include "attributes/renderer_list.h"
#include "scene/scene.h"

namespace Mi { namespace Core {

    void CreateContext(int windowWidth, int windowHeight) {
        if (!glfwInit()) MI_ASSERT("GLFW failed to initialize");

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
#if defined(MI_APPLE_PLATFORM)
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, 1);
#endif

        Mi::Util::MicoreMainwindow = glfwCreateWindow(windowWidth, windowHeight, "Mi Engine for Mac <OpenGL>", NULL, NULL);
        glfwMakeContextCurrent(Mi::Util::MicoreMainwindow);
        glewExperimental=GL_TRUE;
        glewInit();

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_PROGRAM_POINT_SIZE);
    }

    void RunContext(std::function<void()> callback) {

        while (!glfwWindowShouldClose(Mi::Util::MicoreMainwindow)) {

            float startTime = glfwGetTime();
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // Play [Made with Mi] screen
            if (!__mi::__internal::__mi_GAME_DEVELOPMENT_STAGE) {
                std::cout << "hello\n";
            }

            int windowWidth, windowHeight;
            glfwGetWindowSize(Mi::Util::MicoreMainwindow, &windowWidth, &windowHeight);

#if defined(MI_APPLE_PLATFORM)
            glViewport(0, -abs(windowWidth - windowHeight)/2, windowWidth*2, windowWidth*2);
#elif defined(MI_WINDOW_PLATFORM)

#endif
            callback();
            glfwPollEvents();
            glfwSwapBuffers(Mi::Util::MicoreMainwindow);

            float endTime = glfwGetTime();
            deltaTime = endTime - startTime;
        }
    }
}}