#include <private/Managers/InstanceExtensionsManager.h>

#include <GLFW/glfw3.h>

#include <stdexcept>

namespace VT
{
InstanceExtensionsManager::InstanceExtensionsManager()
{
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, availableExtensions.data());

    this->SetAvailableExtensions(availableExtensions);
}

std::vector<const char*> InstanceExtensionsManager::GetMinimalExtensionNames(bool enableValidationLayers)
{
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    std::vector<const char*> extensions;

    for (uint32_t i = 0; i < glfwExtensionCount; ++i)
    {
        const char* extension = glfwExtensions[i];
        if (this->CheckExtensionSupport(extension))
            extensions.push_back(extension);
        else
            throw std::runtime_error(std::string("Extension is not available ") + extension);
    }

    if (enableValidationLayers)
    {
        if (this->CheckExtensionSupport(VK_EXT_DEBUG_REPORT_EXTENSION_NAME))
            extensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
        else
            throw std::runtime_error(std::string("Extension is not available ") + VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
    }

    return extensions;
}
}
