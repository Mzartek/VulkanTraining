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
    virtual ~VTDeviceExtensionsManager() = default;
    VTDeviceExtensionsManager(const VTDeviceExtensionsManager& other) = delete;
    VTDeviceExtensionsManager(VTDeviceExtensionsManager&& other) = delete;
    VTDeviceExtensionsManager& operator=(const VTDeviceExtensionsManager& other) = delete;
    VTDeviceExtensionsManager& operator=(VTDeviceExtensionsManager&& other) = delete;

    std::vector<const char*> GetMinimalExtensionNames(bool enableValidationLayers) override;
};
}

#endif
