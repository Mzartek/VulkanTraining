#include <private/Managers/DeviceLayersManager.h>

namespace VT
{
DeviceLayersManager::DeviceLayersManager(const PhysicalDevice& physicalDevice)
{
    uint32_t layerCount = 0;
    vkEnumerateDeviceLayerProperties(physicalDevice.GetPhysicalDevice(), &layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateDeviceLayerProperties(physicalDevice.GetPhysicalDevice(), &layerCount, availableLayers.data());

    this->SetAvailableLayers(availableLayers);
}

std::vector<const char*> DeviceLayersManager::GetMinimalLayerNames(bool /*enableValidationLayers*/)
{
    return {};
}
}
