#ifndef VT_QUEUE_FAMILIES_MANAGER_INCLUDE_H
#define VT_QUEUE_FAMILIES_MANAGER_INCLUDE_H

#include "VTPhysicalDevice.h"
#include "VTSurface.h"

namespace VT
{
class VTQueueFamiliesManager
{
public:
    VTQueueFamiliesManager(const VTPhysicalDevice& vtPhysicalDevice, const VTSurface& vtSurface);
    virtual ~VTQueueFamiliesManager() = default;
    VTQueueFamiliesManager(const VTQueueFamiliesManager& other) = delete;
    VTQueueFamiliesManager(VTQueueFamiliesManager&& other) = delete;
    VTQueueFamiliesManager& operator=(const VTQueueFamiliesManager& other) = delete;
    VTQueueFamiliesManager& operator=(VTQueueFamiliesManager&& other) = delete;

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
