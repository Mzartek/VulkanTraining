#include "VTLayersManager.h"

#include <cstring>

namespace VT
{
bool VTLayersManager::CheckLayerSupport(const char* layerName)
{
    for (const auto& layer : m_availableLayers)
        if (strcmp(layerName, layer.layerName) == 0)
            return true;

    return false;
}

void VTLayersManager::SetAvailableLayers(const std::vector<VkLayerProperties>& availableLayers)
{
    m_availableLayers = availableLayers;
}
}
