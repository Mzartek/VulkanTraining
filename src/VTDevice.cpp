#include "VTDevice.h"

#include "VTDeviceExtensionsManager.h"
#include "VTDeviceLayersManager.h"

#include <stdexcept>

namespace VT
{
VTDevice::VTDevice(const VTPhysicalDevice& vtPhysicalDevice, bool enableValidationLayers)
    : m_device(VK_NULL_HANDLE)
{
    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    // Graphics Queue
    {
        float queuePriority = 1.0f;
        const auto graphicsQueueInfos = vtPhysicalDevice.GetGraphicsQueueInfos();
        if (graphicsQueueInfos.first < 0)
            throw std::runtime_error("Failed to retrieve graphics queue infos");

        m_graphicsQueueIndex = graphicsQueueInfos.first;
        m_graphicsQueueCount = graphicsQueueInfos.second.queueCount;

        VkDeviceQueueCreateInfo queueCreateInfo = {};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = m_graphicsQueueIndex;
        queueCreateInfo.queueCount = m_graphicsQueueCount;
        queueCreateInfo.pQueuePriorities = &queuePriority;

        queueCreateInfos.push_back(queueCreateInfo);
    }

    VTDeviceExtensionsManager extensionsManager(vtPhysicalDevice);
    VTDeviceLayersManager layersManager(vtPhysicalDevice);

    auto extensionNames = extensionsManager.GetMinimalExtensionNames(enableValidationLayers);
    auto layerNames = layersManager.GetMinimalLayerNames(enableValidationLayers);

    VkPhysicalDeviceFeatures deviceFeatures = vtPhysicalDevice.GetPhysicalDeviceFeatures();

    VkDeviceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
    createInfo.pQueueCreateInfos = queueCreateInfos.data();
    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensionNames.size());
    createInfo.ppEnabledExtensionNames = extensionNames.data();
    createInfo.enabledLayerCount= static_cast<uint32_t>(layerNames.size());
    createInfo.ppEnabledLayerNames = layerNames.data();
    createInfo.pEnabledFeatures = &deviceFeatures;

    VkResult result = vkCreateDevice(vtPhysicalDevice.GetPhysicalDevice(), &createInfo, nullptr, &m_device);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Failed to create device");
}

VTDevice::~VTDevice()
{
    vkDestroyDevice(m_device, nullptr);
}

VkDevice VTDevice::GetDevice()
{
    return m_device;
}

const VkDevice VTDevice::GetDevice() const
{
    return m_device;
}
}
