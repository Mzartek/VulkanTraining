#include "VTInstance.h"

#include <iostream>
#include <cstring>

namespace
{
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

    InitAvailableExtensions();
    InitAvailableLayers();

    auto extensionNames = GetExtensionNames(enableValidationLayers);
    auto layerNames = GetLayerNames(enableValidationLayers);

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

const VkInstance VTInstance::GetInstance() const
{
    return m_instance;
}

void VTInstance::InitAvailableExtensions()
{
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    m_availableExtensions.resize(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, m_availableExtensions.data());
}

void VTInstance::InitAvailableLayers()
{
    uint32_t layerCount = 0;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    m_availableLayers.resize(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, m_availableLayers.data());
}

bool VTInstance::CheckExtensionSupport(const char* extensionName)
{
    for (const auto& extension : m_availableExtensions)
        if (strcmp(extensionName, extension.extensionName) == 0)
            return true;

    return false;
}

bool VTInstance::CheckLayerSupport(const char* layerName)
{
    for (const auto& layer : m_availableLayers)
        if (strcmp(layerName, layer.layerName) == 0)
            return true;

    return false;
}

std::vector<const char*> VTInstance::GetExtensionNames(bool enableValidationLayers)
{
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;

    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    std::vector<const char*> extensions;
    for (uint32_t i = 0; i < glfwExtensionCount; ++i)
    {
        if (CheckExtensionSupport(glfwExtensions[i]))
            extensions.push_back(glfwExtensions[i]);
        else
            throw std::runtime_error("A required extension is not available");
    }

    if (enableValidationLayers)
        extensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);

    return extensions;
}

std::vector<const char*> VTInstance::GetLayerNames(bool enableValidationLayers)
{
    if (!enableValidationLayers) return {};

    const char* standardValidationLayer = "VK_LAYER_LUNARG_standard_validation";
    if (!CheckLayerSupport(standardValidationLayer))
        throw std::runtime_error("A required layer is not available");

    return { standardValidationLayer };
}
}
