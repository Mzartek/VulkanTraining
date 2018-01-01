#include <private/Manager/LayersManager.h>

#include <cstring>

namespace VT
{
bool LayersManager::CheckLayerSupport(const char* layerName)
{
    for (const auto& layer : m_availableLayers)
        if (strcmp(layerName, layer.layerName) == 0)
            return true;

    return false;
}

void LayersManager::SetAvailableLayers(const std::vector<VkLayerProperties>& availableLayers)
{
    m_availableLayers = availableLayers;
}
}
