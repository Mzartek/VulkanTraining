#include <private/Managers/QueueFamiliesManager.h>

namespace VT
{
QueueFamiliesManager::QueueFamiliesManager(const PhysicalDevice& physicalDevice, const Surface& surface)
    : m_hasTransferQueue(false)
    , m_hasGraphicsQueue(false)
    , m_hasComputeQueue(false)
    , m_hasPresentQueue(false)
    , m_transferQueueIndex(0)
    , m_graphicsQueueIndex(0)
    , m_computeQueueIndex(0)
    , m_presentQueueIndex(0)
{
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice.GetPhysicalDevice(), &queueFamilyCount, nullptr);

    m_queueFamilyProperties.resize(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice.GetPhysicalDevice(), &queueFamilyCount, m_queueFamilyProperties.data());

    for (uint32_t i = 0; i < m_queueFamilyProperties.size(); ++i)
    {
        const auto& queueFamily = m_queueFamilyProperties[i];
        if (queueFamily.queueCount)
        {
            if (queueFamily.queueFlags & VK_QUEUE_TRANSFER_BIT)
            {
                m_hasTransferQueue = true;
                m_transferQueueIndex = i;
            }

            if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
            {
                m_hasGraphicsQueue = true;
                m_graphicsQueueIndex = i;
            }

            if (queueFamily.queueFlags & VK_QUEUE_COMPUTE_BIT)
            {
                m_hasComputeQueue = true;
                m_computeQueueIndex = i;
            }

            VkBool32 presentSupport = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice.GetPhysicalDevice(), i, surface.GetSurface(), &presentSupport);
            if (presentSupport)
            {
                m_hasPresentQueue = true;
                m_presentQueueIndex = i;
            }
        }
    }
}

bool QueueFamiliesManager::HasTransferQueue() const
{
    return m_hasTransferQueue;
}

bool QueueFamiliesManager::HasGraphicsQueue() const
{
    return m_hasGraphicsQueue;
}

bool QueueFamiliesManager::HasComputeQueue() const
{
    return m_hasComputeQueue;
}

bool QueueFamiliesManager::HasPresentQueue() const
{
    return m_hasPresentQueue;
}

uint32_t QueueFamiliesManager::GetTransferQueueIndex() const
{
    return m_transferQueueIndex;
}

uint32_t QueueFamiliesManager::GetGraphicsQueueIndex() const
{
    return m_graphicsQueueIndex;
}

uint32_t QueueFamiliesManager::GetComputeQueueIndex() const
{
    return m_computeQueueIndex;
}

uint32_t QueueFamiliesManager::GetPresentQueueIndex() const
{
    return m_presentQueueIndex;
}

uint32_t QueueFamiliesManager::GetIndexQueueCount(uint32_t index) const
{
    return m_queueFamilyProperties[index].queueCount;
}
}
