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
    virtual ~VTDeviceLayersManager() = default;
    VTDeviceLayersManager(const VTDeviceLayersManager& other) = delete;
    VTDeviceLayersManager(VTDeviceLayersManager&& other) = delete;
    VTDeviceLayersManager& operator=(const VTDeviceLayersManager& other) = delete;
    VTDeviceLayersManager& operator=(VTDeviceLayersManager&& other) = delete;

    std::vector<const char*> GetMinimalLayerNames(bool enableValidationLayers) override;
};
}

#endif
