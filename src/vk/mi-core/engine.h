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

namespace Mi { namespace __DEBUG {

    bool __CHECK_VALIDATION_LAYER() {
        uint32_t lCount;
        vkEnumerateInstanceLayerProperties(&lCount, nullptr);
        std::vector<VkLayerProperties> availableLayers(lCount);
        vkEnumerateInstanceLayerProperties(&lCount, availableLayers.data());

        for (const char* lName: validationLayers) {
            bool found = false;

            for (const auto& lProp: availableLayers) {
                if (strcmp(lName, lProp.layerName) == 0) {
                    found = true;
                    break;
                }
            }

            if (!found) {
                return false;
            }
        }

        return true;
    }
}}

namespace Mi { namespace Engine {

    VkInstance instance;
    VkPhysicalDevice __physical_Device = VK_NULL_HANDLE;
    VkDevice __device;

    void Begin(int width, int height) {

        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        main_wind = glfwCreateWindow(width, height, "Vulkan", nullptr, nullptr);

        if (enableValidationLayers && !Mi::__DEBUG::__CHECK_VALIDATION_LAYER()) throw std::runtime_error("No validation layers");

        VkApplicationInfo appInfo{};
        appInfo.sType               = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName    = "Mi Vulkan Support";
        appInfo.applicationVersion  = VK_MAKE_VERSION(1,0,0);
        appInfo.pEngineName         = "Mi";
        appInfo.engineVersion       = VK_MAKE_VERSION(1,0,0);
        appInfo.apiVersion          = VK_API_VERSION_1_0;

        VkInstanceCreateInfo cInfo{};
        cInfo.sType             = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        cInfo.pApplicationInfo  = &appInfo;

        uint32_t glfwExts;
        const char** glfwExt;

        glfwExt = glfwGetRequiredInstanceExtensions(&glfwExts);
        cInfo.enabledExtensionCount     = glfwExts;
        cInfo.ppEnabledExtensionNames   = glfwExt;
        cInfo.enabledLayerCount         = 0;

        if (enableValidationLayers) {
            cInfo.enabledLayerCount     = static_cast<uint32_t>(validationLayers.size());
            cInfo.ppEnabledLayerNames   = validationLayers.data();
        }

        if (vkCreateInstance(&cInfo, nullptr, &instance) != VK_SUCCESS) {
            std::cout << "Cannot create instance\n";
        }

        uint32_t dCount = 0;
        vkEnumeratePhysicalDevices(instance, &dCount, nullptr);
        std::vector<VkPhysicalDevice> __devices(dCount);
        vkEnumeratePhysicalDevices(instance, &dCount, __devices.data());

        for (VkPhysicalDevice d : __devices) {
            VkPhysicalDeviceProperties deviceProperties;
            VkPhysicalDeviceFeatures deviceFeatures;
            vkGetPhysicalDeviceProperties(d, &deviceProperties);
            vkGetPhysicalDeviceFeatures(d, &deviceFeatures);
            if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
                __physical_Device = d;
                break;
            }
        }


    }

    void StartMainLoop() {

        while (!glfwWindowShouldClose(main_wind)) {
            glfwPollEvents();
            glfwSwapBuffers(main_wind);
        }

        vkDestroyInstance(instance, nullptr);
    }
}}