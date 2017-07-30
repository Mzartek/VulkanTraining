#include "VTDeviceExtensionsManager.h"

#include <stdexcept>

namespace VT
{
VTDeviceExtensionsManager::VTDeviceExtensionsManager(const VTPhysicalDevice& vtPhysicalDevice)
{
    uint32_t extensionCount = 0;
    vkEnumerateDeviceExtensionProperties(vtPhysicalDevice.GetPhysicalDevice(), nullptr, &extensionCount, nullptr);

    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateDeviceExtensionProperties(vtPhysicalDevice.GetPhysicalDevice(), nullptr, &extensionCount, availableExtensions.data());

    this->SetAvailableExtensions(availableExtensions);
}

std::vector<const char*> VTDeviceExtensionsManager::GetMinimalExtensionNames(bool /*enableValidationLayers*/)
{
    std::vector<const char*> extensions;
    if (this->CheckExtensionSupport(VK_KHR_SWAPCHAIN_EXTENSION_NAME))
        extensions.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
    else
        std::runtime_error("Swapchain extension is not available");

    return extensions;
}
}
