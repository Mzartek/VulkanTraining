#include <private/GraphicsCommandPool.h>

#include <stdexcept>

namespace VT
{
GraphicsCommandPool::GraphicsCommandPool(Device& device)
    : m_device(device)
    , m_graphicsCommandPool(VK_NULL_HANDLE)
{
    VkCommandPoolCreateInfo poolInfo = {};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.queueFamilyIndex = m_device.GetGraphicsQueueIndex();
    poolInfo.flags = 0;

    VkResult result = vkCreateCommandPool(m_device.GetDevice(), &poolInfo, nullptr, &m_graphicsCommandPool);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Failed to create command pool");
}

GraphicsCommandPool::~GraphicsCommandPool()
{
    vkDestroyCommandPool(m_device.GetDevice(), m_graphicsCommandPool, nullptr);
}

Device& GraphicsCommandPool::GetRelatedDevice() const
{
    return m_device;
}

VkCommandPool GraphicsCommandPool::GetGraphicsCommandPool() const
{
    return m_graphicsCommandPool;
}
}
