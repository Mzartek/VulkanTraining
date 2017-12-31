#include <VulkanTraining/Instance.h>

#include <VulkanTraining/Manager/InstanceExtensionsManager.h>
#include <VulkanTraining/Manager/InstanceLayersManager.h>

#include <iostream>
#include <cstring>

namespace
{
VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
    VkDebugReportFlagsEXT /*flags*/,
    VkDebugReportObjectTypeEXT /*objType*/,
    uint64_t /*obj*/,
    size_t /*location*/,
    int32_t /*code*/,
    const char* /*layerPrefix*/,
    const char* msg,
    void* /*userData*/)
{
    std::cerr << "Validation layer: " << msg << std::endl;

    return VK_FALSE;
}
}

namespace VT
{
Instance::Instance(const std::string& applicationName, bool enableValidationLayers)
    : m_instance(VK_NULL_HANDLE)
    , m_callback(VK_NULL_HANDLE)
{
    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = applicationName.c_str();
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "VT";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    InstanceExtensionsManager extensionsManager;
    InstanceLayersManager layersManager;

    auto extensionNames = extensionsManager.GetMinimalExtensionNames(enableValidationLayers);
    auto layerNames = layersManager.GetMinimalLayerNames(enableValidationLayers);

    VkInstanceCreateInfo instanceCreateInfo = {};
    instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceCreateInfo.pApplicationInfo = &appInfo;
    instanceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(extensionNames.size());
    instanceCreateInfo.ppEnabledExtensionNames = extensionNames.data();
    instanceCreateInfo.enabledLayerCount = static_cast<uint32_t>(layerNames.size());
    instanceCreateInfo.ppEnabledLayerNames = layerNames.data();

    VkResult result = vkCreateInstance(&instanceCreateInfo, nullptr, &m_instance);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Failed to create instance");

    if (enableValidationLayers)
    {
        VkDebugReportCallbackCreateInfoEXT debugReportCallbackCreateInfo = {};
        debugReportCallbackCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
        debugReportCallbackCreateInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
        debugReportCallbackCreateInfo.pfnCallback = debugCallback;

        result = vkCreateDebugReportCallbackEXT(m_instance, &debugReportCallbackCreateInfo, nullptr, &m_callback);
        if (result != VK_SUCCESS)
            throw std::runtime_error("Failed to create callback");
    }
}

Instance::~Instance()
{
    if (m_callback != VK_NULL_HANDLE)
        vkDestroyDebugReportCallbackEXT(m_instance, m_callback, nullptr);
    vkDestroyInstance(m_instance, nullptr);
}

VkInstance Instance::GetInstance()
{
    return m_instance;
}

VkInstance Instance::GetInstance() const
{
    return m_instance;
}
}
