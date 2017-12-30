#ifndef VT_DEVICE_LAYERS_MANAGER_INCLUDE_H
#define VT_DEVICE_LAYERS_MANAGER_INCLUDE_H

#include "VTLayersManager.h"
#include "VTPhysicalDevice.h"

namespace VT
{
class LIB_INTERFACE DeviceLayersManager final : public LayersManager
{
public:
    DeviceLayersManager(const PhysicalDevice& physicalDevice);
    virtual ~DeviceLayersManager() = default;

    std::vector<const char*> GetMinimalLayerNames(bool enableValidationLayers) override;
};
}

#endif
