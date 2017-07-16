#ifndef VT_PHYSICAL_DEVICE_INCLUDE_H
#define VT_PHYSICAL_DEVICE_INCLUDE_H

#include "VTInstance.h"
#include "VTSurface.h"

namespace VT
{
class VTPhysicalDevice
{
public:
    VTPhysicalDevice(const VTInstance& vtInstance, const VTSurface& vtSurface);
    virtual ~VTPhysicalDevice() = default;
    VTPhysicalDevice(const VTPhysicalDevice& other) = delete;
    VTPhysicalDevice(VTPhysicalDevice&& other) = delete;
    VTPhysicalDevice& operator=(const VTPhysicalDevice& other) = delete;
    VTPhysicalDevice& operator=(VTPhysicalDevice&& other) = delete;

    VkPhysicalDevice GetPhysicalDevice();
    VkPhysicalDevice GetPhysicalDevice() const;

    const VkPhysicalDeviceProperties GetPhysicalDeviceProperties() const;
    const VkPhysicalDeviceFeatures GetPhysicalDeviceFeatures() const;

    uint32_t GetQueueCount(uint32_t index) const;

    uint32_t GetGraphicsQueueIndex() const;
    uint32_t GetPresentQueueIndex() const;

private:
    VkPhysicalDevice m_physicalDevice;

    std::vector<VkQueueFamilyProperties> m_queueFamilyProperties;

    uint32_t m_graphicsQueueIndex;
    uint32_t m_presentQueueIndex;
};
}

#endif
