#ifndef VT_DEVICE_INCLUDE_H
#define VT_DEVICE_INCLUDE_H

#include "PhysicalDevice.h"
#include "Surface.h"

namespace VT
{
class Device : public NonCopyableObject
{
public:
    Device(PhysicalDevice& physicalDevice, Surface& surface, bool enableValidationLayers);
    ~Device() override;

    PhysicalDevice& GetRelatedPhysicalDevice() const;
    Surface& GetRelatedSurface() const;

    uint32_t GetTransferQueueIndex() const;
    uint32_t GetGraphicsQueueIndex() const;
    uint32_t GetComputeQueueIndex() const;
    uint32_t GetPresentQueueIndex() const;

    VkDevice GetDevice() const;

    const std::vector<VkQueue>& GetTransferQueues() const;
    const std::vector<VkQueue>& GetGraphicsQueues() const;
    const std::vector<VkQueue>& GetComputeQueues() const;
    const std::vector<VkQueue>& GetPresentQueues() const;

    VkCommandPool GetTransferCommandPool() const;
    VkCommandPool GetGraphicsCommandPool() const;
    VkCommandPool GetComputeCommandPool() const;

private:
    PhysicalDevice& m_physicalDevice;
    Surface& m_surface;

    uint32_t m_transferQueueIndex;
    uint32_t m_graphicsQueueIndex;
    uint32_t m_computeQueueIndex;
    uint32_t m_presentQueueIndex;

    VkDevice m_device;

    std::vector<VkQueue> m_transferQueues;
    std::vector<VkQueue> m_graphicsQueues;
    std::vector<VkQueue> m_computeQueues;
    std::vector<VkQueue> m_presentQueues;

    VkCommandPool m_transferCommandPool;
    VkCommandPool m_graphicsCommandPool;
    VkCommandPool m_computeCommandPool;
};
}

#endif
