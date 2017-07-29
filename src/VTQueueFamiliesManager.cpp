#include "VTQueueFamiliesManager.h"

namespace VT
{
VTQueueFamiliesManager::VTQueueFamiliesManager(const VTPhysicalDevice& vtPhysicalDevice, const VTSurface& vtSurface)
    : m_hasGraphicsQueue(false)
    , m_hasPresentQueue(false)
    , m_graphicsQueueIndex(0)
    , m_presentQueueIndex(0)
{
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(vtPhysicalDevice.GetPhysicalDevice(), &queueFamilyCount, nullptr);

    m_queueFamilyProperties.resize(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(vtPhysicalDevice.GetPhysicalDevice(), &queueFamilyCount, m_queueFamilyProperties.data());

    for (uint32_t i = 0; i < m_queueFamilyProperties.size(); ++i)
    {
        const auto& queueFamily = m_queueFamilyProperties[i];
        if (queueFamily.queueCount)
        {
            if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
            {
                m_hasGraphicsQueue = true;
                m_graphicsQueueIndex = i;
            }

            VkBool32 presentSupport = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(vtPhysicalDevice.GetPhysicalDevice(), i, vtSurface.GetSurface(), &presentSupport);
            if (presentSupport)
            {
                m_hasPresentQueue = true;
                m_presentQueueIndex = i;
            }
        }

    }
}

bool VTQueueFamiliesManager::HasGraphicsQueue() const
{
    return m_hasGraphicsQueue;
}

bool VTQueueFamiliesManager::HasPresentQueue() const
{
    return m_hasPresentQueue;
}

uint32_t VTQueueFamiliesManager::GetGraphicsQueueIndex() const
{
    return m_graphicsQueueIndex;
}

uint32_t VTQueueFamiliesManager::GetPresentQueueIndex() const
{
    return m_presentQueueIndex;
}

uint32_t VTQueueFamiliesManager::GetIndexQueueCount(uint32_t index) const
{
    return m_queueFamilyProperties[index].queueCount;
}
}
