#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <optional>

GLFWwindow* main_wind;
VkInstance instance;
VkDevice __device;
VkPhysicalDevice physicalDevice;
const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};
#ifdef NDEBUG
    const bool enableValidationLayers = false;
#else
    const bool enableValidationLayers = true;
#endif

#define LOG1(x) std::cout << x << std::endl;
#define LOG2(x, y) std::cout << x << " " << y << std::endl;
#define LOG3(x, y, z) std::cout << x << " " << y << " " << z << std::endl;


namespace Mi { namespace Engine {

    void vMiEngineBegin(int width, int height) {

        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        main_wind = glfwCreateWindow(width, height, "Vulkan", nullptr, nullptr);

        
    }

    void vMiEngineStartMainLoop() {

        while (!glfwWindowShouldClose(main_wind)) {
            glfwPollEvents();
            glfwSwapBuffers(main_wind);
        }

        vkDestroyInstance(instance, nullptr);
    }
}}