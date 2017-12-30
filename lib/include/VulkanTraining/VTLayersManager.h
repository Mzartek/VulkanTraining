#ifndef VT_LAYERS_MANAGER_INCLUDE_H
#define VT_LAYERS_MANAGER_INCLUDE_H

#include "VTExport.h"

#include <vulkan/vulkan.h>

#include <vector>

namespace VT
{
class LIB_INTERFACE LayersManager
{
public:
    LayersManager() = default;
    virtual ~LayersManager() = default;

    bool CheckLayerSupport(const char* layerName);

    virtual std::vector<const char*> GetMinimalLayerNames(bool enableValidationLayers) = 0;

protected:
    void SetAvailableLayers(const std::vector<VkLayerProperties>& availableLayers);

private:
    std::vector<VkLayerProperties> m_availableLayers;
};
}

#endif
