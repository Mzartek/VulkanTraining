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

    std::vector<const char*> GetMinimalExtensionNames(bool enableValidationLayers) override;
};
}

#endif
