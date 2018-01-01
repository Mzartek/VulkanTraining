#ifndef VT_DEVICE_INCLUDE_H
#define VT_DEVICE_INCLUDE_H

#include "PhysicalDevice.h"
#include "Surface.h"

namespace VT
{
class Device
{
public:
    Device(const PhysicalDevice& physicalDevice, const Surface& surface, bool enableValidationLayers);
    virtual ~Device();
    Device(const Device& other) = delete;
    Device(Device&& other) = delete;
    Device& operator=(const Device& other) = delete;
    Device& operator=(Device&& other) = delete;

    VkDevice GetDevice();
    VkDevice GetDevice() const;

    const PhysicalDevice& GetRelatedPhysicalDevice() const;
    const Surface& GetRelatedSurface() const;

    const std::vector<VkQueue>& GetGraphicsQueues() const;
    const std::vector<VkQueue>& GetPresentQueues() const;

private:
    const PhysicalDevice& m_physicalDevice;
    const Surface& m_surface;
    VkDevice m_device;

    std::vector<VkQueue> m_graphicsQueues;
    std::vector<VkQueue> m_presentQueues;
};
}

#endif
