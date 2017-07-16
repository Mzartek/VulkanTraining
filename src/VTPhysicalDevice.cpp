#include "VTPhysicalDevice.h"

#include <stdexcept>
#include <map>

namespace
{
struct QueueFamiliesHelper
{
    QueueFamiliesHelper(const VkPhysicalDevice& physicalDevice, const VkSurfaceKHR& surface)
        : m_hasGraphicsQueue(false)
        , m_hasPresentQueue(false)
        , m_graphicsQueueIndex(0)
        , m_presentQueueIndex(0)
    {
        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);

        m_queueFamilyProperties.resize(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, m_queueFamilyProperties.data());

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
                vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, i, surface, &presentSupport);
                if (presentSupport)
                {
                    m_hasPresentQueue = true;
                    m_presentQueueIndex = i;
                }
            }

        }
    }

    bool IsComplete() const
    {
        return m_hasGraphicsQueue && m_hasPresentQueue;
    }

    std::vector<VkQueueFamilyProperties> GetQueueFamilyProperties()
    {
        return m_queueFamilyProperties;
    }

    uint32_t GetGraphicsQueueIndex() const
    {
        return m_graphicsQueueIndex;
    }

    uint32_t GetPresentQueueIndex() const
    {
        return m_presentQueueIndex;
    }

private:
    std::vector<VkQueueFamilyProperties> m_queueFamilyProperties;

    bool m_hasGraphicsQueue;
    bool m_hasPresentQueue;

    uint32_t m_graphicsQueueIndex;
    uint32_t m_presentQueueIndex;
};

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
VTPhysicalDevice::VTPhysicalDevice(const VTInstance& vtInstance, const VTSurface& vtSurface)
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
        const QueueFamiliesHelper queueFamiliesHelper(physicalDevice, vtSurface.GetSurface());
        if (queueFamiliesHelper.IsComplete())
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
            m_queueFamilyProperties = candidates.rbegin()->second.second.GetQueueFamilyProperties();
            m_graphicsQueueIndex = candidates.rbegin()->second.second.GetGraphicsQueueIndex();
            m_presentQueueIndex = candidates.rbegin()->second.second.GetPresentQueueIndex();
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

uint32_t VTPhysicalDevice::GetQueueCount(uint32_t index) const
{
    return m_queueFamilyProperties[index].queueCount;
}

uint32_t VTPhysicalDevice::GetGraphicsQueueIndex() const
{
    return m_graphicsQueueIndex;
}

uint32_t VTPhysicalDevice::GetPresentQueueIndex() const
{
    return m_presentQueueIndex;
}
}
