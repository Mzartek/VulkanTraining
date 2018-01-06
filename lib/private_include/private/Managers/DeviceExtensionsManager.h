#ifndef VT_DEVICE_EXTENSIONS_MANAGER_INCLUDE_H
#define VT_DEVICE_EXTENSIONS_MANAGER_INCLUDE_H

#include "ExtensionsManager.h"
#include "../PhysicalDevice.h"

namespace VT
{
class DeviceExtensionsManager final : public ExtensionsManager
{
public:
    DeviceExtensionsManager(const PhysicalDevice& physicalDevice);
    ~DeviceExtensionsManager() override = default;

    std::vector<const char*> GetMinimalExtensionNames(bool enableValidationLayers) override;
};
}

#endif
