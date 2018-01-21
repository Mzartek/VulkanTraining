#ifndef VT_QUEUE_FAMILIES_MANAGER_INCLUDE_H
#define VT_QUEUE_FAMILIES_MANAGER_INCLUDE_H

#include "../PhysicalDevice.h"
#include "../Surface.h"

namespace VT
{
class QueueFamiliesManager
{
public:
    QueueFamiliesManager(const PhysicalDevice& physicalDevice, const Surface& surface);
    virtual ~QueueFamiliesManager() = default;

    bool HasTransferQueue() const;
    bool HasGraphicsQueue() const;
    bool HasComputeQueue() const;
    bool HasPresentQueue() const;

    uint32_t GetTransferQueueIndex() const;
    uint32_t GetGraphicsQueueIndex() const;
    uint32_t GetComputeQueueIndex() const;
    uint32_t GetPresentQueueIndex() const;

    uint32_t GetIndexQueueCount(uint32_t index) const;

private:
    std::vector<VkQueueFamilyProperties> m_queueFamilyProperties;

    bool m_hasTransferQueue;
    bool m_hasGraphicsQueue;
    bool m_hasComputeQueue;
    bool m_hasPresentQueue;

    uint32_t m_transferQueueIndex;
    uint32_t m_graphicsQueueIndex;
    uint32_t m_computeQueueIndex;
    uint32_t m_presentQueueIndex;
};
}

#endif
