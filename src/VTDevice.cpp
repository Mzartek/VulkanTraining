#include "VTDevice.h"

#include "VTQueueFamiliesManager.h"
#include "VTDeviceExtensionsManager.h"
#include "VTDeviceLayersManager.h"

#include <set>
#include <stdexcept>

namespace VT
{
VTDevice::VTDevice(const VTPhysicalDevice& vtPhysicalDevice, const VTSurface& vtSurface, bool enableValidationLayers)
    : m_physicalDevice(vtPhysicalDevice)
    , m_surface(vtSurface)
    , m_device(VK_NULL_HANDLE)
{
    VTQueueFamiliesManager vtQueueFamiliesManager(vtPhysicalDevice, vtSurface);

    if (!vtQueueFamiliesManager.HasGraphicsQueue())
        throw std::runtime_error("PhysicalDevice doesn't have Graphics Queue");
    if (!vtQueueFamiliesManager.HasPresentQueue())
        throw std::runtime_error("PhysicalDevice doesn't have Present Queue");

    std::set<uint32_t> queueFamilyIndexes =
    {
        vtQueueFamiliesManager.GetGraphicsQueueIndex(),
        vtQueueFamiliesManager.GetPresentQueueIndex()
    };

    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    const float queuePriority = 1.0f;
    for (uint32_t queueFamilyIndex : queueFamilyIndexes)
    {
        VkDeviceQueueCreateInfo queueCreateInfo = {};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = queueFamilyIndex;
        queueCreateInfo.queueCount = vtQueueFamiliesManager.GetIndexQueueCount(queueFamilyIndex);
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

    const uint32_t graphicsQueueFamilyIndex = vtQueueFamiliesManager.GetGraphicsQueueIndex();
    m_graphicsQueues.resize(vtQueueFamiliesManager.GetIndexQueueCount(graphicsQueueFamilyIndex));
    for (uint32_t i = 0; i < m_graphicsQueues.size(); ++i)
        vkGetDeviceQueue(m_device, graphicsQueueFamilyIndex, i, &m_graphicsQueues[i]);

    const uint32_t presentQueueFamilyIndex = vtQueueFamiliesManager.GetPresentQueueIndex();
    m_presentQueues.resize(vtQueueFamiliesManager.GetIndexQueueCount(presentQueueFamilyIndex));
    for (uint32_t i = 0; i < m_presentQueues.size(); ++i)
        vkGetDeviceQueue(m_device, presentQueueFamilyIndex, i, &m_presentQueues[i]);
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

const VTPhysicalDevice& VTDevice::GetRelatedPhysicalDevice() const
{
    return m_physicalDevice;
}

const VTSurface& VTDevice::GetRelatedSurface() const
{
    return m_surface;
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
