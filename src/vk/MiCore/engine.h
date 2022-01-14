#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>

GLFWwindow* main_wind;
VkInstance instance;

namespace vmi_engine {

    void vMiEngineBegin(int width, int height) {

        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        main_wind = glfwCreateWindow(width, height, "Vulkan", nullptr, nullptr);

        VkApplicationInfo ainfo = {};
        ainfo.sType                 = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        ainfo.pApplicationName      = "Mi Engine";
        ainfo.applicationVersion    = VK_MAKE_VERSION(1, 0, 0);
        ainfo.pEngineName           = "Mi Engine";
        ainfo.engineVersion         = VK_MAKE_VERSION(1, 0, 0);
        ainfo.apiVersion            = VK_API_VERSION_1_0;

        VkInstanceCreateInfo cinfo = {};
        cinfo.sType                 = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        cinfo.pApplicationInfo      = &ainfo;


        uint32_t glfwextc = 0;
        const char** glfwexts;

        glfwexts = glfwGetRequiredInstanceExtensions(&glfwextc);

        cinfo.enabledExtensionCount     = glfwextc;
        cinfo.ppEnabledExtensionNames   = glfwexts;
        cinfo.enabledLayerCount         = 0;

        VkResult res = vkCreateInstance(&cinfo, NULL, &instance);

        if (res != VK_SUCCESS) throw std::runtime_error("Failed to create instance");
    }

    void vMiEngineStartMainLoop() {

        while (!glfwWindowShouldClose(main_wind)) {
            glfwPollEvents();
            glfwSwapBuffers(main_wind);
        }

        vkDestroyInstance(instance, nullptr);
    }
}