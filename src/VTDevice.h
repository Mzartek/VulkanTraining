#ifndef VT_DEVICE_INCLUDE_H
#define VT_DEVICE_INCLUDE_H

#include "VTPhysicalDevice.h"

namespace VT
{
class VTDevice
{
public:
    VTDevice(const VTPhysicalDevice& vtPhysicalDevice, bool enableValidationLayers);
    virtual ~VTDevice();
    VTDevice(const VTDevice& other) = delete;
    VTDevice(VTDevice&& other) = delete;
    VTDevice& operator=(const VTDevice& other) = delete;
    VTDevice& operator=(VTDevice&& other) = delete;

    VkDevice GetDevice();
    VkDevice GetDevice() const;

    std::vector<VkQueue> GetGraphicsQueues() const;

private:
    const VTPhysicalDevice& m_physicalDevice;
    VkDevice m_device;
};
}

#endif
