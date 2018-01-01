#ifndef VT_DEVICE_LAYERS_MANAGER_INCLUDE_H
#define VT_DEVICE_LAYERS_MANAGER_INCLUDE_H

#include "LayersManager.h"
#include "../PhysicalDevice.h"

namespace VT
{
class DeviceLayersManager final : public LayersManager
{
public:
    DeviceLayersManager(const PhysicalDevice& physicalDevice);
    virtual ~DeviceLayersManager() = default;

    std::vector<const char*> GetMinimalLayerNames(bool enableValidationLayers) override;
};
}

#endif
