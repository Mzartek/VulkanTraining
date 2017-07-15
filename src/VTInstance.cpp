#include "VTInstance.h"

#include "VTInstanceExtensionsManager.h"
#include "VTInstanceLayersManager.h"

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
VTInstance::VTInstance(const VTWindow& vtWindow, bool enableValidationLayers)
    : m_instance(VK_NULL_HANDLE)
    , m_callback(VK_NULL_HANDLE)
{
    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = vtWindow.GetTitle().c_str();
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "VT";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VTInstanceExtensionsManager extensionsManager;
    VTInstanceLayersManager layersManager;

    auto extensionNames = extensionsManager.GetMinimalExtensionNames(enableValidationLayers);
    auto layerNames = layersManager.GetMinimalLayerNames(enableValidationLayers);

    VkInstanceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensionNames.size());
    createInfo.ppEnabledExtensionNames = extensionNames.data();
    createInfo.enabledLayerCount = static_cast<uint32_t>(layerNames.size());
    createInfo.ppEnabledLayerNames = layerNames.data();

    VkResult result = vkCreateInstance(&createInfo, nullptr, &m_instance);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Failed to create instance");

    if (enableValidationLayers)
    {
        VkDebugReportCallbackCreateInfoEXT createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
        createInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
        createInfo.pfnCallback = debugCallback;

        result = vkCreateDebugReportCallbackEXT(m_instance, &createInfo, nullptr, &m_callback);
        if (result != VK_SUCCESS)
            throw std::runtime_error("Failed to create callback");
    }
}

VTInstance::~VTInstance()
{
    if (m_callback != VK_NULL_HANDLE)
        vkDestroyDebugReportCallbackEXT(m_instance, m_callback, nullptr);
    vkDestroyInstance(m_instance, nullptr);
}

VkInstance VTInstance::GetInstance()
{
    return m_instance;
}

VkInstance VTInstance::GetInstance() const
{
    return m_instance;
}
}
