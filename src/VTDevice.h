#ifndef VT_DEVICE_INCLUDE_H
#define VT_DEVICE_INCLUDE_H

#include "VTPhysicalDevice.h"
#include "VTSurface.h"

namespace VT
{
class VTDevice
{
public:
    VTDevice(const VTPhysicalDevice& vtPhysicalDevice, const VTSurface& vtSurface, bool enableValidationLayers);
    virtual ~VTDevice();
    VTDevice(const VTDevice& other) = delete;
    VTDevice(VTDevice&& other) = delete;
    VTDevice& operator=(const VTDevice& other) = delete;
    VTDevice& operator=(VTDevice&& other) = delete;

    VkDevice GetDevice();
    VkDevice GetDevice() const;

    const VTPhysicalDevice& GetRelatedPhysicalDevice() const;
    const VTSurface& GetRelatedSurface() const;

    const std::vector<VkQueue>& GetGraphicsQueues() const;
    const std::vector<VkQueue>& GetPresentQueues() const;

private:
    const VTPhysicalDevice& m_physicalDevice;
    const VTSurface& m_surface;
    VkDevice m_device;

    std::vector<VkQueue> m_graphicsQueues;
    std::vector<VkQueue> m_presentQueues;
};
}

#endif
