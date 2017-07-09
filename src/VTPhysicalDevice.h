#ifndef VT_PHYSICAL_DEVICE_INCLUDE_H
#define VT_PHYSICAL_DEVICE_INCLUDE_H

#include "VTInstance.h"

namespace VT
{
class VTPhysicalDevice
{
public:
    VTPhysicalDevice(const VTInstance& vtInstance);
    virtual ~VTPhysicalDevice() = default;
    VTPhysicalDevice(const VTPhysicalDevice& other) = delete;
    VTPhysicalDevice(VTPhysicalDevice&& other) = delete;
    VTPhysicalDevice& operator=(const VTPhysicalDevice& other) = delete;
    VTPhysicalDevice& operator=(VTPhysicalDevice&& other) = delete;

    VkPhysicalDevice GetPhysicalDevice();
    const VkPhysicalDevice GetPhysicalDevice() const;

private:
    VkPhysicalDevice m_physicalDevice;
};
}

#endif
