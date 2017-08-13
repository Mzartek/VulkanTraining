#ifndef VT_DEVICE_LAYERS_MANAGER_INCLUDE_H
#define VT_DEVICE_LAYERS_MANAGER_INCLUDE_H

#include "VTLayersManager.h"
#include "VTPhysicalDevice.h"

namespace VT
{
class DeviceLayersManager final : public LayersManager
{
public:
    DeviceLayersManager(const PhysicalDevice& physicalDevice);
    virtual ~DeviceLayersManager() = default;
    DeviceLayersManager(const DeviceLayersManager& other) = delete;
    DeviceLayersManager(DeviceLayersManager&& other) = delete;
    DeviceLayersManager& operator=(const DeviceLayersManager& other) = delete;
    DeviceLayersManager& operator=(DeviceLayersManager&& other) = delete;

    std::vector<const char*> GetMinimalLayerNames(bool enableValidationLayers) override;
};
}

#endif
