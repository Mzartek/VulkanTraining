#include "VTPhysicalDevice.h"

#include <stdexcept>
#include <map>

namespace
{
struct QueueFamiliesHelper
{
    QueueFamiliesHelper(const VkPhysicalDevice& physicalDevice)
        : m_hasGraphicsQueue(false)
        , m_graphicsQueueIndex(0)
        , m_graphicsQueueCount(0)
    {
        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);

        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies.data());

        for (uint32_t i = 0; i < queueFamilies.size(); ++i)
        {
            const auto& queueFamily = queueFamilies[i];
            if (queueFamily.queueCount)
            {
                if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
                {
                    m_hasGraphicsQueue = true;
                    m_graphicsQueueIndex = i;
                    m_graphicsQueueCount = queueFamily.queueCount;
                }
            }

        }
    }

    bool HasGraphicsQueue() const
    {
        return m_hasGraphicsQueue;
    }

    uint32_t GetGraphicsQueueIndex() const
    {
        return m_graphicsQueueIndex;
    }

    uint32_t GetGraphicsQueueCount() const
    {
        return m_graphicsQueueCount;
    }

private:
    bool m_hasGraphicsQueue;
    uint32_t m_graphicsQueueIndex;
    uint32_t m_graphicsQueueCount;
};

bool AreQueueFamiliesSuitable(const QueueFamiliesHelper& queueFamiliesHelper)
{
    if (queueFamiliesHelper.HasGraphicsQueue())
        return true;
    return false;
}

int RatePhysicalDeviceSuitability(VkPhysicalDevice physicalDevice)
{
    VkPhysicalDeviceProperties physicalDeviceProperties;
    VkPhysicalDeviceFeatures physicalDeviceFeatures;
    vkGetPhysicalDeviceProperties(physicalDevice, &physicalDeviceProperties);
    vkGetPhysicalDeviceFeatures(physicalDevice, &physicalDeviceFeatures);

    int score = physicalDeviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU ? 1000 : 0;
    score += physicalDeviceProperties.limits.maxImageDimension2D;
    score += physicalDeviceFeatures.geometryShader ? 100 : 0;

    return score;
}
}

namespace VT
{
VTPhysicalDevice::VTPhysicalDevice(const VTInstance& vtInstance)
    : m_physicalDevice(VK_NULL_HANDLE)
{
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(vtInstance.GetInstance(), &deviceCount, nullptr);

    if (deviceCount == 0)
        throw std::runtime_error("Failed to find GPUs with Vulkan support");

    std::vector<VkPhysicalDevice> physicalDevices(deviceCount);
    vkEnumeratePhysicalDevices(vtInstance.GetInstance(), &deviceCount, physicalDevices.data());

    std::multimap<int, std::pair<VkPhysicalDevice, QueueFamiliesHelper>> candidates;

    for (const auto& physicalDevice : physicalDevices)
    {
        const QueueFamiliesHelper queueFamiliesHelper(physicalDevice);
        if (AreQueueFamiliesSuitable(queueFamiliesHelper))
        {
            const int score = RatePhysicalDeviceSuitability(physicalDevice);
            candidates.insert({ score, { physicalDevice, queueFamiliesHelper }});
        }
    }

    if (!candidates.empty())
    {
        if (candidates.rbegin()->first > 0)
        {
            m_physicalDevice = candidates.rbegin()->second.first;
            m_graphicsQueueIndex = candidates.rbegin()->second.second.GetGraphicsQueueIndex();
            m_graphicsQueueCount = candidates.rbegin()->second.second.GetGraphicsQueueCount();
        }
    }
    else
        throw std::runtime_error("Failed to find a suitable GPU");
}

VkPhysicalDevice VTPhysicalDevice::GetPhysicalDevice()
{
    return m_physicalDevice;
}

VkPhysicalDevice VTPhysicalDevice::GetPhysicalDevice() const
{
    return m_physicalDevice;
}

const VkPhysicalDeviceProperties VTPhysicalDevice::GetPhysicalDeviceProperties() const
{
    VkPhysicalDeviceProperties physicalDeviceProperties;
    vkGetPhysicalDeviceProperties(m_physicalDevice, &physicalDeviceProperties);

    return physicalDeviceProperties;
}

const VkPhysicalDeviceFeatures VTPhysicalDevice::GetPhysicalDeviceFeatures() const
{
    VkPhysicalDeviceFeatures physicalDeviceFeatures;
    vkGetPhysicalDeviceFeatures(m_physicalDevice, &physicalDeviceFeatures);

    return physicalDeviceFeatures;
}

uint32_t VTPhysicalDevice::GetGraphicsQueueIndex() const
{
    return m_graphicsQueueIndex;
}

uint32_t VTPhysicalDevice::GetGraphicsQueueCount() const
{
    return m_graphicsQueueCount;
}
}
