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


namespace vmi_engine {

    struct QueueFamilyIndices {
        std::optional<uint32_t> gFamily;  
    };

    QueueFamilyIndices __vMiFindQueue(VkPhysicalDevice device) {
        QueueFamilyIndices indices;

        uint32_t familyc;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &familyc, nullptr);

        std::vector<VkQueueFamilyProperties> qProp(familyc);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &familyc, qProp.data());

        int index = 0;
        for (const auto& qfamily : qProp) {
            if (qfamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) indices.gFamily = index;
            index++;
        }
        return indices;
    }

    bool __vMiIsDeviceSuitable(VkPhysicalDevice device) {
        QueueFamilyIndices indices = __vMiFindQueue(device);
        return indices.gFamily.has_value();
    }

    bool __vMiCheckValidationLayer() {
        uint32_t layerc;
        vkEnumerateInstanceLayerProperties(&layerc, nullptr);

        std::vector<VkLayerProperties> layers(layerc);
        vkEnumerateInstanceLayerProperties(&layerc, layers.data());

        for (const char* layern : validationLayers) {
            bool found = false;

            for (const auto& lprop : layers) {
                if (strcmp(layern, lprop.layerName) == 0) {
                    found = true;
                    break;
                }
            }

            if (!found) return false;
        }

        return true;
    }

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


        uint32_t glfwextc   = 0;
        uint32_t devicec    = 0;
        const char** glfwexts;

        glfwexts = glfwGetRequiredInstanceExtensions(&glfwextc);

        cinfo.enabledExtensionCount         = glfwextc;
        cinfo.ppEnabledExtensionNames       = glfwexts;

        if (enableValidationLayers && !__vMiCheckValidationLayer()) throw std::runtime_error("No validation layers available");
        if (enableValidationLayers) { 
            cinfo.enabledLayerCount         = static_cast<uint32_t>(validationLayers.size());
            cinfo.ppEnabledLayerNames       = validationLayers.data();
        }
        else cinfo.enabledLayerCount        = 0;

        VkResult res = vkCreateInstance(&cinfo, NULL, &instance);
        if (res != VK_SUCCESS) throw std::runtime_error("Failed to create instance");

        vkEnumeratePhysicalDevices(instance, &devicec, nullptr);
        std::vector<VkPhysicalDevice> devices(devicec);
        vkEnumeratePhysicalDevices(instance, &devicec, devices.data());


        for (const auto& device : devices) {
            if (__vMiIsDeviceSuitable(device)) {
                physicalDevice = device;
                break;
            }
        }

        VkPhysicalDeviceFeatures deviceFeatures;
        vkGetPhysicalDeviceFeatures(physicalDevice, &deviceFeatures);

        QueueFamilyIndices indices = __vMiFindQueue(physicalDevice);
        VkDeviceQueueCreateInfo queueInfo = {};
        queueInfo.sType                 = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueInfo.queueFamilyIndex      = indices.gFamily.value();
        queueInfo.queueCount            = 1;
        float qPriority                 = 1.0f;
        queueInfo.pQueuePriorities      = &qPriority;

        VkDeviceCreateInfo deviceInfo = {};
        deviceInfo.sType                    = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        deviceInfo.pQueueCreateInfos        = &queueInfo;
        deviceInfo.queueCreateInfoCount     = 1;
        deviceInfo.pEnabledFeatures         = &deviceFeatures;
        deviceInfo.enabledExtensionCount    = 0;

        if (enableValidationLayers) {
            deviceInfo.enabledLayerCount    = static_cast<uint32_t>(validationLayers.size());
            deviceInfo.ppEnabledLayerNames  = validationLayers.data();
        }
        else deviceInfo.enabledLayerCount   = 0;

        if (vkCreateDevice(physicalDevice, &deviceInfo, nullptr, &__device) != VK_SUCCESS) {
            
        }
    }

    void vMiEngineStartMainLoop() {

        while (!glfwWindowShouldClose(main_wind)) {
            glfwPollEvents();
            glfwSwapBuffers(main_wind);
        }

        vkDestroyInstance(instance, nullptr);
    }
}