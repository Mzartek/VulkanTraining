#include <private/Managers/InstanceLayersManager.h>

#include <stdexcept>

namespace VT
{
InstanceLayersManager::InstanceLayersManager()
{
    uint32_t layerCount = 0;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    this->SetAvailableLayers(availableLayers);
}

std::vector<const char*> InstanceLayersManager::GetMinimalLayerNames(bool enableValidationLayers)
{
    if (!enableValidationLayers) return {};

    const char* standardValidationLayer = "VK_LAYER_LUNARG_standard_validation";
    if (!this->CheckLayerSupport(standardValidationLayer))
        throw std::runtime_error("A required layer is not available");

    return { standardValidationLayer };
}
}
