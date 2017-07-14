#ifndef VT_DEVICE_LAYERS_MANAGER_INCLUDE_H
#define VT_DEVICE_LAYERS_MANAGER_INCLUDE_H

#include "VTLayersManager.h"
#include "VTPhysicalDevice.h"

namespace VT
{
class VTDeviceLayersManager final : public VTLayersManager
{
public:
    VTDeviceLayersManager(const VTPhysicalDevice& vtPhysicalDevice);

    std::vector<const char*> GetMinimalLayerNames(bool enableValidationLayers) override;
};
}

#endif
