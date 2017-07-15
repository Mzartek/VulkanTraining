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
    return {};
}
}
