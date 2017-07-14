#ifndef VT_INSTANCE_LAYERS_MANAGER_INCLUDE_H
#define VT_INSTANCE_LAYERS_MANAGER_INCLUDE_H

#include "VTLayersManager.h"

namespace VT
{
class VTInstanceLayersManager final : public VTLayersManager
{
public:
    VTInstanceLayersManager();

    std::vector<const char*> GetMinimalLayerNames(bool enableValidationLayers) override;
};
}

#endif
