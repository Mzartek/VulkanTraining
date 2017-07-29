#ifndef VT_INSTANCE_LAYERS_MANAGER_INCLUDE_H
#define VT_INSTANCE_LAYERS_MANAGER_INCLUDE_H

#include "VTLayersManager.h"

namespace VT
{
class VTInstanceLayersManager final : public VTLayersManager
{
public:
    VTInstanceLayersManager();
    virtual ~VTInstanceLayersManager() = default;
    VTInstanceLayersManager(const VTInstanceLayersManager& other) = delete;
    VTInstanceLayersManager(VTInstanceLayersManager&& other) = delete;
    VTInstanceLayersManager& operator=(const VTInstanceLayersManager& other) = delete;
    VTInstanceLayersManager& operator=(VTInstanceLayersManager&& other) = delete;

    std::vector<const char*> GetMinimalLayerNames(bool enableValidationLayers) override;
};
}

#endif
