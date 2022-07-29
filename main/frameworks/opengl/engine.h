#if defined(_WIN32)
    #if defined(_WIN64)
        #define MI_WINDOW_PLATFORM
    #endif

#elif defined(__APPLE__) || defined(__MACH__)
    #define MI_APPLE_PLATFORM

#elif defined(__linux__)
    #define MI_LINUX_PLATFORM
#endif

#define MI_ENGINE_OPENGL
#define LOGOUT(x) std::cout << x << '\n'
#define MI_ASSERT(msg) throw std::runtime_error(msg)

#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <memory>
#include <functional>
#include <string>
#include <glm/glm.hpp>

namespace Mi::Util {
    GLFWwindow* MicoreMainwindow;
}

// Mi Registry
//#include <Mi-Attrib/registry.h>
#include <errors.h>
#include "attributes/renderer_list.h"
#include "scene/scene.h"

namespace Mi::Core {

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
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            int windowWidth, windowHeight;
            glfwGetWindowSize(Mi::Util::MicoreMainwindow, &windowWidth, &windowHeight);

#if defined(MI_APPLE_PLATFORM)
            glViewport(0, -abs(windowWidth - windowHeight)/2, windowWidth*2, windowWidth*2);
#elif defined(MI_WINDOW_PLATFORM)

#endif
            callback();
            glfwPollEvents();
            glfwSwapBuffers(Mi::Util::MicoreMainwindow);
        }
    }
}