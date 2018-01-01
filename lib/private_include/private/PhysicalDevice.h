#ifndef VT_PHYSICAL_DEVICE_INCLUDE_H
#define VT_PHYSICAL_DEVICE_INCLUDE_H

#include "Instance.h"

#include <vector>

namespace VT
{
class PhysicalDevice
{
    static std::vector<VkPhysicalDevice> AvailablePhysicalDevices;

public:
    PhysicalDevice(const Instance& instance);
    virtual ~PhysicalDevice() = default;
    PhysicalDevice(const PhysicalDevice& other) = delete;
    PhysicalDevice(PhysicalDevice&& other) = delete;
    PhysicalDevice& operator=(const PhysicalDevice& other) = delete;
    PhysicalDevice& operator=(PhysicalDevice&& other) = delete;

    VkPhysicalDevice GetPhysicalDevice();
    VkPhysicalDevice GetPhysicalDevice() const;

    const VkPhysicalDeviceProperties GetPhysicalDeviceProperties() const;
    const VkPhysicalDeviceFeatures GetPhysicalDeviceFeatures() const;

private:
    VkPhysicalDevice m_physicalDevice;
};
}

#endif
