#include "VTInstanceLayersManager.h"

#include <stdexcept>

namespace VT
{
VTInstanceLayersManager::VTInstanceLayersManager()
{
    uint32_t layerCount = 0;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    this->SetAvailableLayers(availableLayers);
}

std::vector<const char*> VTInstanceLayersManager::GetMinimalLayerNames(bool enableValidationLayers)
{
    if (!enableValidationLayers) return {};

    const char* standardValidationLayer = "VK_LAYER_LUNARG_standard_validation";
    if (!this->CheckLayerSupport(standardValidationLayer))
        throw std::runtime_error("A required layer is not available");

    return { standardValidationLayer };
}
}
