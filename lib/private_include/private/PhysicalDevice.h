#ifndef VT_PHYSICAL_DEVICE_INCLUDE_H
#define VT_PHYSICAL_DEVICE_INCLUDE_H

#include "Instance.h"

#include <vector>

namespace VT
{
class PhysicalDevice : public NonCopyableObject
{
    static std::vector<VkPhysicalDevice> AvailablePhysicalDevices;

public:
    PhysicalDevice(const Instance& instance);

    VkPhysicalDevice GetPhysicalDevice() const;

    const VkPhysicalDeviceProperties GetPhysicalDeviceProperties() const;
    const VkPhysicalDeviceFeatures GetPhysicalDeviceFeatures() const;

private:
    VkPhysicalDevice m_physicalDevice;
};
}

#endif
