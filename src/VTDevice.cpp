#include "VTDevice.h"

#include "VTDeviceExtensionsManager.h"
#include "VTDeviceLayersManager.h"

#include <stdexcept>

namespace VT
{
VTDevice::VTDevice(const VTPhysicalDevice& vtPhysicalDevice, bool enableValidationLayers)
    : m_physicalDevice(vtPhysicalDevice)
    , m_device(VK_NULL_HANDLE)
{
    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    // Graphics Queue
    {
        float queuePriority = 1.0f;

        VkDeviceQueueCreateInfo queueCreateInfo = {};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = m_physicalDevice.GetGraphicsQueueIndex();
        queueCreateInfo.queueCount = m_physicalDevice.GetGraphicsQueueCount();
        queueCreateInfo.pQueuePriorities = &queuePriority;

        queueCreateInfos.push_back(queueCreateInfo);
    }

    VTDeviceExtensionsManager extensionsManager(m_physicalDevice);
    VTDeviceLayersManager layersManager(m_physicalDevice);

    auto extensionNames = extensionsManager.GetMinimalExtensionNames(enableValidationLayers);
    auto layerNames = layersManager.GetMinimalLayerNames(enableValidationLayers);

    VkPhysicalDeviceFeatures deviceFeatures = m_physicalDevice.GetPhysicalDeviceFeatures();

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

VkDevice VTDevice::GetDevice() const
{
    return m_device;
}

std::vector<VkQueue> VTDevice::GetGraphicsQueues() const
{
    std::vector<VkQueue> graphicsQueues(m_physicalDevice.GetGraphicsQueueCount());
    for (uint32_t i = 0; i < graphicsQueues.size(); ++i)
        vkGetDeviceQueue(m_device, m_physicalDevice.GetGraphicsQueueIndex(), i, &graphicsQueues[i]);

    return graphicsQueues;
}
}
