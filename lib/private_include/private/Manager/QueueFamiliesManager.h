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

    bool HasGraphicsQueue() const;
    bool HasPresentQueue() const;

    uint32_t GetGraphicsQueueIndex() const;
    uint32_t GetPresentQueueIndex() const;

    uint32_t GetIndexQueueCount(uint32_t index) const;

private:
    std::vector<VkQueueFamilyProperties> m_queueFamilyProperties;

    bool m_hasGraphicsQueue;
    bool m_hasPresentQueue;

    uint32_t m_graphicsQueueIndex;
    uint32_t m_presentQueueIndex;
};
}

#endif
