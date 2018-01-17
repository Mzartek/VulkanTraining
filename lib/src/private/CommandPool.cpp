#include <private/CommandPool.h>

#include <stdexcept>

namespace VT
{
CommandPool::CommandPool(Device& device)
    : m_device(device)
    , m_commandPool(VK_NULL_HANDLE)
{
    VkCommandPoolCreateInfo poolInfo = {};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.queueFamilyIndex = m_device.GetGraphicsQueueIndex();
    poolInfo.flags = 0;

    VkResult result = vkCreateCommandPool(m_device.GetDevice(), &poolInfo, nullptr, &m_commandPool);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Failed to create command pool");
}

CommandPool::~CommandPool()
{
    vkDestroyCommandPool(m_device.GetDevice(), m_commandPool, nullptr);
}

Device& CommandPool::GetRelatedDevice() const
{
    return m_device;
}

VkCommandPool CommandPool::GetCommandPool() const
{
    return m_commandPool;
}
}
