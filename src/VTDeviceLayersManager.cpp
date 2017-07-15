#include "VTDeviceLayersManager.h"

namespace VT
{
VTDeviceLayersManager::VTDeviceLayersManager(const VTPhysicalDevice& vtPhysicalDevice)
{
    uint32_t layerCount = 0;
    vkEnumerateDeviceLayerProperties(vtPhysicalDevice.GetPhysicalDevice(), &layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateDeviceLayerProperties(vtPhysicalDevice.GetPhysicalDevice(), &layerCount, availableLayers.data());

    this->SetAvailableLayers(availableLayers);
}

std::vector<const char*> VTDeviceLayersManager::GetMinimalLayerNames(bool /*enableValidationLayers*/)
{
    return {};
}
}
