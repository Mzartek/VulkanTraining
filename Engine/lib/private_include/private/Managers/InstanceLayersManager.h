#ifndef VT_INSTANCE_LAYERS_MANAGER_INCLUDE_H
#define VT_INSTANCE_LAYERS_MANAGER_INCLUDE_H

#include "LayersManager.h"

namespace VT
{
class InstanceLayersManager final : public LayersManager
{
public:
    InstanceLayersManager();
    ~InstanceLayersManager() override = default;

    std::vector<const char*> GetMinimalLayerNames(bool enableValidationLayers) override;
};
}

#endif
