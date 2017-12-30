#ifndef VT_INSTANCE_LAYERS_MANAGER_INCLUDE_H
#define VT_INSTANCE_LAYERS_MANAGER_INCLUDE_H

#include "VTLayersManager.h"

namespace VT
{
class LIB_INTERFACE InstanceLayersManager final : public LayersManager
{
public:
    InstanceLayersManager();
    virtual ~InstanceLayersManager() = default;

    std::vector<const char*> GetMinimalLayerNames(bool enableValidationLayers) override;
};
}

#endif
