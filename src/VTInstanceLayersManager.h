#ifndef VT_INSTANCE_LAYERS_MANAGER_INCLUDE_H
#define VT_INSTANCE_LAYERS_MANAGER_INCLUDE_H

#include "VTLayersManager.h"

namespace VT
{
class InstanceLayersManager final : public LayersManager
{
public:
    InstanceLayersManager();
    virtual ~InstanceLayersManager() = default;
    InstanceLayersManager(const InstanceLayersManager& other) = delete;
    InstanceLayersManager(InstanceLayersManager&& other) = delete;
    InstanceLayersManager& operator=(const InstanceLayersManager& other) = delete;
    InstanceLayersManager& operator=(InstanceLayersManager&& other) = delete;

    std::vector<const char*> GetMinimalLayerNames(bool enableValidationLayers) override;
};
}

#endif
