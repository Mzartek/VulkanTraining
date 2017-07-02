#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <iostream>
#include <stdexcept>
#include <functional>
#include <vector>
#include <cstring>

constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;

#ifdef NDEBUG
constexpr bool enableValidationLayers = false;
#else
constexpr bool enableValidationLayers = true;
#endif

class HelloTriangleApplication
{
public:
    HelloTriangleApplication()
    {
        uint32_t extensionCount = 0;
        uint32_t layerCount = 0;

        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

        availableExtensions.resize(extensionCount);
        availableLayers.resize(layerCount);

        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, availableExtensions.data());
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());
    }

    void run()
    {
        initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }

private:
    GLFWwindow* window;

    std::vector<VkExtensionProperties> availableExtensions;
    std::vector<VkLayerProperties> availableLayers;

    VkInstance m_instance = VK_NULL_HANDLE;
    VkDebugReportCallbackEXT m_callback = VK_NULL_HANDLE;
    VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;

    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
        VkDebugReportFlagsEXT flags,
        VkDebugReportObjectTypeEXT objType,
        uint64_t obj,
        size_t location,
        int32_t code,
        const char* layerPrefix,
        const char* msg,
        void* userData)
    {
        std::cerr << "Validation layer: " << msg << std::endl;

        return VK_FALSE;
    }

    bool checkExtensionSupport(const char* extensionName)
    {
        for (const auto& extension : availableExtensions)
            if (strcmp(extensionName, extension.extensionName) == 0)
                return true;

        return false;
    }

    bool checkLayerSupport(const char* layerName)
    {
        for (const auto& layer : availableLayers)
            if (strcmp(layerName, layer.layerName) == 0)
                return true;

        return false;
    }

    std::vector<const char*> getExtensionNames()
    {
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;

        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        std::vector<const char*> extensions;
        for (uint32_t i = 0; i < glfwExtensionCount; ++i)
        {
            if (checkExtensionSupport(glfwExtensions[i]))
                extensions.push_back(glfwExtensions[i]);
            else
                throw std::runtime_error("A required extension is not available");
        }

        if (enableValidationLayers)
            extensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);

        return extensions;
    }

    std::vector<const char*> getLayerNames()
    {
        if (!enableValidationLayers) return {};

        const char* standardValidationLayer = "VK_LAYER_LUNARG_standard_validation";
        if (!checkLayerSupport(standardValidationLayer))
            throw std::runtime_error("A required layer is not available");

        return { standardValidationLayer };
    }

    bool isPhysicalDeviceSuitable(VkPhysicalDevice physicalDevice)
    {
        return true;
    }

    void initWindow()
    {
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
    }

    void initVulkan()
    {
        createInstance();
        setupDebugCallback();
        pickPhysicalDevice();
    }

    void createInstance()
    {
        VkApplicationInfo appInfo = {};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Hello Triangle";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        auto extensionNames = getExtensionNames();
        auto layerNames = getLayerNames();

        VkInstanceCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;
        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensionNames.size());
        createInfo.ppEnabledExtensionNames = extensionNames.data();
        createInfo.enabledLayerCount = static_cast<uint32_t>(layerNames.size());
        createInfo.ppEnabledLayerNames = layerNames.data();

        if (vkCreateInstance(&createInfo, nullptr, &m_instance) != VK_SUCCESS)
            throw std::runtime_error("Failed to create instance");

        std::cout << "Enabled extensions:" << std::endl;
        for (const auto& extensionName : extensionNames)
            std::cout << "\t" << extensionName << std::endl;

        std::cout << "Enabled layers;" << std::endl;
        for (const auto& layerName : layerNames)
            std::cout << "\t" << layerName << std::endl;
    }

    void setupDebugCallback()
    {
        if (!enableValidationLayers) return;

        VkDebugReportCallbackCreateInfoEXT createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
        createInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
        createInfo.pfnCallback = debugCallback;

        if (vkCreateDebugReportCallbackEXT(m_instance, &createInfo, nullptr, &m_callback) != VK_SUCCESS)
            throw std::runtime_error("Failed to set up debug callback");
    }

    void pickPhysicalDevice()
    {
        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(m_instance, &deviceCount, nullptr);

        if (deviceCount == 0)
            throw std::runtime_error("Failed to find GPUs with Vulkan support");

        std::vector<VkPhysicalDevice> physicalDevices(deviceCount);
        vkEnumeratePhysicalDevices(m_instance, &deviceCount, physicalDevices.data());

        for (const auto& physicalDevice : physicalDevices)
        {
            if (isPhysicalDeviceSuitable(physicalDevice))
            {
                m_physicalDevice = physicalDevice;
                break;
            }
        }

        if (m_physicalDevice == VK_NULL_HANDLE)
            throw std::runtime_error("Failed to find a suitable GPU");
    }

    void mainLoop()
    {
        while (!glfwWindowShouldClose(window))
        {
            glfwPollEvents();
        }
    }

    void cleanup()
    {
        vkDestroyDebugReportCallbackEXT(m_instance, m_callback, nullptr);
        vkDestroyInstance(m_instance, nullptr);

        glfwDestroyWindow(window);

        glfwTerminate();
    }
};

int main()
{
    HelloTriangleApplication app;

    try
    {
        app.run();
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
