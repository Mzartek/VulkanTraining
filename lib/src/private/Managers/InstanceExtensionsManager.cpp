#include <private/Managers/InstanceExtensionsManager.h>

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
    std::vector<const char*> extensions;

    extensions.push_back(VK_KHR_SURFACE_EXTENSION_NAME);

#if defined(VK_USE_PLATFORM_WIN32_KHR)
    extensions.push_back(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);
#endif

#if defined(VK_USE_PLATFORM_XLIB_KHR)
    extensions.push_back(VK_KHR_XLIB_SURFACE_EXTENSION_NAME);
#endif

#if defined(VK_USE_PLATFORM_XCB_KHR)
    extensions.push_back(VK_KHR_XCB_SURFACE_EXTENSION_NAME);
#endif

#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
    extensions.push_back(VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME);
#endif

    if (enableValidationLayers)
        extensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);

    for (auto& extension : extensions)
        if (!this->CheckExtensionSupport(extension))
            throw std::runtime_error(std::string("Extension is not available ") + extension);

    return extensions;
}
}
