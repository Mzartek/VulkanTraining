#include "VTInstanceExtensionsManager.h"

#include <GLFW/glfw3.h>

#include <stdexcept>

namespace VT
{
VTInstanceExtensionsManager::VTInstanceExtensionsManager()
{
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, availableExtensions.data());

    this->SetAvailableExtensions(availableExtensions);
}

std::vector<const char*> VTInstanceExtensionsManager::GetMinimalExtensionNames(bool enableValidationLayers)
{
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;

    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    std::vector<const char*> extensions;
    for (uint32_t i = 0; i < glfwExtensionCount; ++i)
    {
        if (this->CheckExtensionSupport(glfwExtensions[i]))
            extensions.push_back(glfwExtensions[i]);
        else
            throw std::runtime_error("A required extension is not available");
    }

    if (enableValidationLayers)
        extensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);

    return extensions;
}
}
