#include <private/Device.h>

#include <private/Managers/QueueFamiliesManager.h>
#include <private/Managers/DeviceExtensionsManager.h>
#include <private/Managers/DeviceLayersManager.h>

#include <set>
#include <stdexcept>

namespace VT
{
Device::Device(PhysicalDevice& physicalDevice, Surface& surface, bool enableValidationLayers)
    : m_physicalDevice(physicalDevice)
    , m_surface(surface)
    , m_graphicsQueueIndex(0)
    , m_presentQueueIndex(0)
    , m_device(VK_NULL_HANDLE)
{
    QueueFamiliesManager queueFamiliesManager(m_physicalDevice, surface);

    if (!queueFamiliesManager.HasTransferQueue())
        throw std::runtime_error("PhysicalDevice doesn't have Transfer Queue");
    if (!queueFamiliesManager.HasGraphicsQueue())
        throw std::runtime_error("PhysicalDevice doesn't have Graphics Queue");
    if (!queueFamiliesManager.HasComputeQueue())
        throw std::runtime_error("PhysicalDevice doesn't have Compute Queue");
    if (!queueFamiliesManager.HasPresentQueue())
        throw std::runtime_error("PhysicalDevice doesn't have Present Queue");

    m_transferQueueIndex = queueFamiliesManager.GetTransferQueueIndex();
    m_graphicsQueueIndex = queueFamiliesManager.GetGraphicsQueueIndex();
    m_computeQueueIndex = queueFamiliesManager.GetComputeQueueIndex();
    m_presentQueueIndex = queueFamiliesManager.GetPresentQueueIndex();

    std::set<uint32_t> queueFamilyIndexes =
    {
        m_transferQueueIndex,
        m_graphicsQueueIndex,
        m_computeQueueIndex,
        m_presentQueueIndex
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

    m_transferQueues.resize(queueFamiliesManager.GetIndexQueueCount(m_transferQueueIndex));
    for (uint32_t i = 0; i < m_transferQueues.size(); ++i)
        vkGetDeviceQueue(m_device, m_transferQueueIndex, i, &m_transferQueues[i]);

    m_graphicsQueues.resize(queueFamiliesManager.GetIndexQueueCount(m_graphicsQueueIndex));
    for (uint32_t i = 0; i < m_graphicsQueues.size(); ++i)
        vkGetDeviceQueue(m_device, m_graphicsQueueIndex, i, &m_graphicsQueues[i]);

    m_computeQueues.resize(queueFamiliesManager.GetIndexQueueCount(m_computeQueueIndex));
    for (uint32_t i = 0; i < m_computeQueues.size(); ++i)
        vkGetDeviceQueue(m_device, m_computeQueueIndex, i, &m_computeQueues[i]);

    m_presentQueues.resize(queueFamiliesManager.GetIndexQueueCount(m_presentQueueIndex));
    for (uint32_t i = 0; i < m_presentQueues.size(); ++i)
        vkGetDeviceQueue(m_device, m_presentQueueIndex, i, &m_presentQueues[i]);
}

Device::~Device()
{
    vkDestroyDevice(m_device, nullptr);
}

PhysicalDevice& Device::GetRelatedPhysicalDevice() const
{
    return m_physicalDevice;
}

Surface& Device::GetRelatedSurface() const
{
    return m_surface;
}

uint32_t Device::GetGraphicsQueueIndex() const
{
    return m_graphicsQueueIndex;
}

uint32_t Device::GetPresentQueueIndex() const
{
    return m_presentQueueIndex;
}

VkDevice Device::GetDevice() const
{
    return m_device;
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
