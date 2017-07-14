#ifndef VT_DEVICE_EXTENSIONS_MANAGER_INCLUDE_H
#define VT_DEVICE_EXTENSIONS_MANAGER_INCLUDE_H

#include "VTExtensionsManager.h"
#include "VTPhysicalDevice.h"

namespace VT
{
class VTDeviceExtensionsManager final : public VTExtensionsManager
{
public:
    VTDeviceExtensionsManager(const VTPhysicalDevice& vtPhysicalDevice);

    std::vector<const char*> GetMinimalExtensionNames(bool enableValidationLayers) override;
};
}

#endif
