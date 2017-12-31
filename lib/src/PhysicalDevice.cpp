#include <VulkanTraining/PhysicalDevice.h>

#include <algorithm>
#include <stdexcept>
#include <map>

namespace
{
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

void InitAvailablePhysicalDevices(VkInstance instance, std::vector<VkPhysicalDevice>& availablePhysicalDevices)
{
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

    availablePhysicalDevices.resize(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, availablePhysicalDevices.data());

    std::sort(availablePhysicalDevices.begin(), availablePhysicalDevices.end(), [](VkPhysicalDevice a, VkPhysicalDevice b)
    {
        return RatePhysicalDeviceSuitability(a) > RatePhysicalDeviceSuitability(b);
    });
}
}

namespace VT
{
std::vector<VkPhysicalDevice> PhysicalDevice::AvailablePhysicalDevices;

PhysicalDevice::PhysicalDevice(const Instance& instance)
    : m_physicalDevice(VK_NULL_HANDLE)
{
    static bool first = true;
    if (first)
    {
        InitAvailablePhysicalDevices(instance.GetInstance(), AvailablePhysicalDevices);
        first = false;
    }

    if (AvailablePhysicalDevices.empty())
        throw std::runtime_error("No available GPU");

    m_physicalDevice = AvailablePhysicalDevices.front();
}

VkPhysicalDevice PhysicalDevice::GetPhysicalDevice()
{
    return m_physicalDevice;
}

VkPhysicalDevice PhysicalDevice::GetPhysicalDevice() const
{
    return m_physicalDevice;
}

const VkPhysicalDeviceProperties PhysicalDevice::GetPhysicalDeviceProperties() const
{
    VkPhysicalDeviceProperties physicalDeviceProperties;
    vkGetPhysicalDeviceProperties(m_physicalDevice, &physicalDeviceProperties);

    return physicalDeviceProperties;
}

const VkPhysicalDeviceFeatures PhysicalDevice::GetPhysicalDeviceFeatures() const
{
    VkPhysicalDeviceFeatures physicalDeviceFeatures;
    vkGetPhysicalDeviceFeatures(m_physicalDevice, &physicalDeviceFeatures);

    return physicalDeviceFeatures;
}
}
