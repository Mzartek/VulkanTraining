#include "VTDevice.h"

#include "VTDeviceExtensionsManager.h"
#include "VTDeviceLayersManager.h"

#include <set>
#include <stdexcept>

namespace VT
{
VTDevice::VTDevice(const VTPhysicalDevice& vtPhysicalDevice, bool enableValidationLayers)
    : m_physicalDevice(vtPhysicalDevice)
    , m_device(VK_NULL_HANDLE)
{
    std::set<uint32_t> queueFamilyIndexes =
    {
        m_physicalDevice.GetGraphicsQueueIndex(),
        m_physicalDevice.GetPresentQueueIndex()
    };
    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;

    const float queuePriority = 1.0f;
    for (const auto& queueFamilyIndex : queueFamilyIndexes)
    {
        VkDeviceQueueCreateInfo queueCreateInfo = {};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = queueFamilyIndex;
        queueCreateInfo.queueCount = m_physicalDevice.GetQueueCount(queueFamilyIndex);
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

    VkResult result = vkCreateDevice(m_physicalDevice.GetPhysicalDevice(), &createInfo, nullptr, &m_device);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Failed to create device");

    uint32_t queueIndex = m_physicalDevice.GetGraphicsQueueIndex();
    m_graphicsQueues.resize(m_physicalDevice.GetQueueCount(queueIndex));
    for (uint32_t i = 0; i < m_graphicsQueues.size(); ++i)
        vkGetDeviceQueue(m_device, queueIndex, i, &m_graphicsQueues[i]);

    queueIndex = m_physicalDevice.GetPresentQueueIndex();
    m_presentQueues.resize(m_physicalDevice.GetQueueCount(queueIndex));
    for (uint32_t i = 0; i < m_presentQueues.size(); ++i)
        vkGetDeviceQueue(m_device, queueIndex, i, &m_presentQueues[i]);
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

const std::vector<VkQueue>& VTDevice::GetGraphicsQueues() const
{
    return m_graphicsQueues;
}

const std::vector<VkQueue>& VTDevice::GetPresentQueues() const
{
    return m_presentQueues;
}
}
