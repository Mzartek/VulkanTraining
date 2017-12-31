#include <VulkanTraining/Device.h>

#include <VulkanTraining/Manager/QueueFamiliesManager.h>
#include <VulkanTraining/Manager/DeviceExtensionsManager.h>
#include <VulkanTraining/Manager/DeviceLayersManager.h>

#include <set>
#include <stdexcept>

namespace VT
{
Device::Device(const PhysicalDevice& physicalDevice, const Surface& surface, bool enableValidationLayers)
    : m_physicalDevice(physicalDevice)
    , m_surface(surface)
    , m_device(VK_NULL_HANDLE)
{
    QueueFamiliesManager queueFamiliesManager(m_physicalDevice, surface);

    if (!queueFamiliesManager.HasGraphicsQueue())
        throw std::runtime_error("PhysicalDevice doesn't have Graphics Queue");
    if (!queueFamiliesManager.HasPresentQueue())
        throw std::runtime_error("PhysicalDevice doesn't have Present Queue");

    std::set<uint32_t> queueFamilyIndexes =
    {
        queueFamiliesManager.GetGraphicsQueueIndex(),
        queueFamiliesManager.GetPresentQueueIndex()
    };

    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    const float queuePriority = 1.0f;
    for (uint32_t queueFamilyIndex : queueFamilyIndexes)
    {
        VkDeviceQueueCreateInfo queueCreateInfo = {};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = queueFamilyIndex;
        queueCreateInfo.queueCount = queueFamiliesManager.GetIndexQueueCount(queueFamilyIndex);
        queueCreateInfo.pQueuePriorities = &queuePriority;

        queueCreateInfos.push_back(queueCreateInfo);
    }

    DeviceExtensionsManager extensionsManager(m_physicalDevice);
    DeviceLayersManager layersManager(m_physicalDevice);

    auto extensionNames = extensionsManager.GetMinimalExtensionNames(enableValidationLayers);
    auto layerNames = layersManager.GetMinimalLayerNames(enableValidationLayers);

    VkPhysicalDeviceFeatures deviceFeatures = m_physicalDevice.GetPhysicalDeviceFeatures();

    VkDeviceCreateInfo deviceCreateInfo = {};
    deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    deviceCreateInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
    deviceCreateInfo.pQueueCreateInfos = queueCreateInfos.data();
    deviceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(extensionNames.size());
    deviceCreateInfo.ppEnabledExtensionNames = extensionNames.data();
    deviceCreateInfo.enabledLayerCount= static_cast<uint32_t>(layerNames.size());
    deviceCreateInfo.ppEnabledLayerNames = layerNames.data();
    deviceCreateInfo.pEnabledFeatures = &deviceFeatures;

    VkResult result = vkCreateDevice(m_physicalDevice.GetPhysicalDevice(), &deviceCreateInfo, nullptr, &m_device);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Failed to create device");

    const uint32_t graphicsQueueFamilyIndex = queueFamiliesManager.GetGraphicsQueueIndex();
    m_graphicsQueues.resize(queueFamiliesManager.GetIndexQueueCount(graphicsQueueFamilyIndex));
    for (uint32_t i = 0; i < m_graphicsQueues.size(); ++i)
        vkGetDeviceQueue(m_device, graphicsQueueFamilyIndex, i, &m_graphicsQueues[i]);

    const uint32_t presentQueueFamilyIndex = queueFamiliesManager.GetPresentQueueIndex();
    m_presentQueues.resize(queueFamiliesManager.GetIndexQueueCount(presentQueueFamilyIndex));
    for (uint32_t i = 0; i < m_presentQueues.size(); ++i)
        vkGetDeviceQueue(m_device, presentQueueFamilyIndex, i, &m_presentQueues[i]);
}

Device::~Device()
{
    vkDestroyDevice(m_device, nullptr);
}

VkDevice Device::GetDevice()
{
    return m_device;
}

VkDevice Device::GetDevice() const
{
    return m_device;
}

const PhysicalDevice& Device::GetRelatedPhysicalDevice() const
{
    return m_physicalDevice;
}

const Surface& Device::GetRelatedSurface() const
{
    return m_surface;
}

const std::vector<VkQueue>& Device::GetGraphicsQueues() const
{
    return m_graphicsQueues;
}

const std::vector<VkQueue>& Device::GetPresentQueues() const
{
    return m_presentQueues;
}
}
