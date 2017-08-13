#ifndef VT_LAYERS_MANAGER_INCLUDE_H
#define VT_LAYERS_MANAGER_INCLUDE_H

#include <vulkan/vulkan.h>

#include <vector>

namespace VT
{
class LayersManager
{
public:
    LayersManager() = default;
    virtual ~LayersManager() = default;
    LayersManager(const LayersManager& other) = delete;
    LayersManager(LayersManager&& other) = delete;
    LayersManager& operator=(const LayersManager& other) = delete;
    LayersManager& operator=(LayersManager&& other) = delete;

    bool CheckLayerSupport(const char* layerName);

    virtual std::vector<const char*> GetMinimalLayerNames(bool enableValidationLayers) = 0;

protected:
    void SetAvailableLayers(const std::vector<VkLayerProperties>& availableLayers);

private:
    std::vector<VkLayerProperties> m_availableLayers;
};
}

#endif
