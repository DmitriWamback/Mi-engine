#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <string>
#include <thread>
#include <functional>
#include <list>
#include "net/socket_server.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

GLFWwindow* main_window;
#define KEY_UP                  GLFW_PRESS
#define KEY_DOWN                GLFW_RELEASE
#define MOUSE_BUTTON_RIGHT      GLFW_MOUSE_BUTTON_RIGHT
#define MOUSE_BUTTON_LEFT       GLFW_MOUSE_BUTTON_LEFT

#define GetKeyDown(key)             glfwGetKey(main_window, key) == KEY_UP
#define GetKeyUp(key)               glfwGetKey(main_window, key) == KEY_DOWN
#define GetMouseButtonDown(key)     glfwGetMouseButton(main_window, key) == KEY_UP
#define GetMouseButtonUp(key)       glfwGetMouseButton(main_window, key) == KEY_DOWN
void GetMousePosition(double* x, double* y) {
    glfwGetCursorPos(main_window, x, y);
}

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "shader.h"
#include "util/perlin_noise.h"
#include "util/camera.h"
#include "util/renderable.h"

namespace MITI { namespace Core {

    MITI::MITISocketServer serv;
    MITI::Camera camera;
    MITI::Shader main_shader;
    MITI::CoreGraphics::Renderable* renderable;

    void InitializeMITI(int width, int height) {

        serv = MITI::MITISocketServer::CreateLocalhost();
        camera = MITI::Camera::Create();

        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#if defined(__APPLE__)
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif
        main_window = glfwCreateWindow(width, height, "MITI", NULL, NULL);
        glfwMakeContextCurrent(main_window);

        glewExperimental = GL_TRUE;
        glewInit();
    }

    void scroll(GLFWwindow* window, double x, double y) {
        camera.UpdateZoom(y);
    }

    void StartMainLoop() {

        serv.WaitConnection();
        main_shader = MITI::Shader::Create("vMain.glsl", "fMain.glsl", "MAIN_SHADER");

        MITI::CoreGraphics::renderbuf r = MITI::CoreGraphics::renderbuf();
        renderable = MITI::CoreGraphics::Triangle::Create(r);
        glm::mat4 model = glm::mat4(1.f);

        glfwSetScrollCallback(main_window, scroll);

        glEnable(GL_VERTEX_PROGRAM_POINT_SIZE_ARB);
        glEnable(GL_DEPTH_TEST);

        while (!glfwWindowShouldClose(main_window)) {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glClearColor(0.05, 0.05, 0.05, 0.0);

            int width;
            int height;
            glfwGetWindowSize(main_window, &width, &height);

#if defined(__APPLE__)
            if (width > height) glViewport(0, -abs(width-height), width*2, width*2);
            else glViewport(-abs(width-height), 0, height*2, height*2);
#else
            if (width > height) glViewport(0, -abs(width-height)/2, width, width);
            else glViewport(-abs(width-height)/2, 0, height, height);
#endif

            std::string data = serv.Read();
            camera.Update();
            main_shader.use();
            main_shader.setMatr4("projection", camera.projection);
            main_shader.setMatr4("view", camera.view);
            main_shader.setMatr4("model", model);
            renderable->Render();

            glfwPollEvents();
            glfwSwapBuffers(main_window);
        }
    }
}}