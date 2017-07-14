#include "VTPhysicalDevice.h"

#include <stdexcept>
#include <map>

namespace
{
bool IsPhysicalDeviceSuitable(VkPhysicalDevice physicalDevice)
{
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies.data());

    for (const auto& queueFamily : queueFamilies)
        if (queueFamily.queueCount && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
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

    std::multimap<int, VkPhysicalDevice> candidates;

    for (const auto& physicalDevice : physicalDevices)
    {
        if (IsPhysicalDeviceSuitable(physicalDevice))
        {
            const int score = RatePhysicalDeviceSuitability(physicalDevice);
            candidates.insert(std::make_pair(score, physicalDevice));
        }
    }

    if (!candidates.empty())
    {
        if (candidates.rbegin()->first > 0)
            m_physicalDevice = candidates.rbegin()->second;
    }
    else
        throw std::runtime_error("Failed to find a suitable GPU");
}

VkPhysicalDevice VTPhysicalDevice::GetPhysicalDevice()
{
    return m_physicalDevice;
}

const VkPhysicalDevice VTPhysicalDevice::GetPhysicalDevice() const
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

std::pair<int, VkQueueFamilyProperties> VTPhysicalDevice::GetGraphicsQueueInfos() const
{
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(m_physicalDevice, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(m_physicalDevice, &queueFamilyCount, queueFamilies.data());

    for (int i = 0; i < queueFamilies.size(); ++i)
    {
        const auto& queueFamily = queueFamilies[i];
        if (queueFamily.queueCount && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
            return { i, queueFamily };
    }

    return { -1, {} };
}
}
