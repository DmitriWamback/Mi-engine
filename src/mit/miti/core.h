#include <iostream>
#include "net/socket_server.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace MITI { namespace Core {

    MITI::MITISocketServer serv;
    GLFWwindow* main_window;

    void InitializeMITI(int width, int height) {

        serv = MITI::MITISocketServer::CreateLocalhost();

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

    void StartMainLoop() {

        serv.WaitConnection();

        while (!glfwWindowShouldClose(main_window)) {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glClearColor(0.05, 0.05, 0.05, 0.0);

            std::string data = serv.Read();
            std::cout << data << std::endl;

            glfwPollEvents();
            glfwSwapBuffers(main_window);
        }
    }
}}