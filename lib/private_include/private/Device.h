#ifndef VT_DEVICE_INCLUDE_H
#define VT_DEVICE_INCLUDE_H

#include "PhysicalDevice.h"
#include "Surface.h"

namespace VT
{
class Device
{
public:
    Device(PhysicalDevice& physicalDevice, Surface& surface, bool enableValidationLayers);
    virtual ~Device();
    Device(const Device& other) = delete;
    Device(Device&& other) = delete;
    Device& operator=(const Device& other) = delete;
    Device& operator=(Device&& other) = delete;

    PhysicalDevice& GetRelatedPhysicalDevice() const;
    Surface& GetRelatedSurface() const;

    VkDevice GetDevice() const;
    const std::vector<VkQueue>& GetGraphicsQueues() const;
    const std::vector<VkQueue>& GetPresentQueues() const;

private:
    PhysicalDevice& m_physicalDevice;
    Surface& m_surface;

    VkDevice m_device;
    std::vector<VkQueue> m_graphicsQueues;
    std::vector<VkQueue> m_presentQueues;
};
}

#endif
