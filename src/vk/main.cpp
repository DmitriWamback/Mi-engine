#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

GLFWwindow* main_wind;

int main() {

    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    main_wind = glfwCreateWindow(1200, 800, "Vulkan", nullptr, nullptr);

    while (!glfwWindowShouldClose(main_wind)) {
        glfwPollEvents();
        glfwSwapBuffers(main_wind);
    }
}