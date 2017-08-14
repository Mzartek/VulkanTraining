#ifndef VT_DEVICE_EXTENSIONS_MANAGER_INCLUDE_H
#define VT_DEVICE_EXTENSIONS_MANAGER_INCLUDE_H

#include "VTExtensionsManager.h"
#include "VTPhysicalDevice.h"

namespace VT
{
class LIB_INTERFACE DeviceExtensionsManager final : public ExtensionsManager
{
public:
    DeviceExtensionsManager(const PhysicalDevice& physicalDevice);
    virtual ~DeviceExtensionsManager() = default;
    DeviceExtensionsManager(const DeviceExtensionsManager& other) = delete;
    DeviceExtensionsManager(DeviceExtensionsManager&& other) = delete;
    DeviceExtensionsManager& operator=(const DeviceExtensionsManager& other) = delete;
    DeviceExtensionsManager& operator=(DeviceExtensionsManager&& other) = delete;

    std::vector<const char*> GetMinimalExtensionNames(bool enableValidationLayers) override;
};
}

#endif
