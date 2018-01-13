#include <private/CommandPool.h>

#include <private/Managers/QueueFamiliesManager.h>

#include <stdexcept>

namespace VT
{
CommandPool::CommandPool(const Device& device, const IGraphicsPipeline& graphicsPipeline)
    : m_device(device)
    , m_commandPool(VK_NULL_HANDLE)
{
    QueueFamiliesManager queueFamiliesManager(m_device.GetRelatedPhysicalDevice(), m_device.GetRelatedSurface());

    VkCommandPoolCreateInfo poolInfo = {};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.queueFamilyIndex = queueFamiliesManager.GetGraphicsQueueIndex();
    poolInfo.flags = 0;

    VkResult result = vkCreateCommandPool(m_device.GetDevice(), &poolInfo, nullptr, &m_commandPool);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Failed to create command pool");

    m_commandBuffers.resize(graphicsPipeline.GetFramebuffers().size());

    VkCommandBufferAllocateInfo allocInfo = {};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = m_commandPool;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandBufferCount = static_cast<uint32_t>(m_commandBuffers.size());

    result = vkAllocateCommandBuffers(m_device.GetDevice(), &allocInfo, m_commandBuffers.data());
    if (result != VK_SUCCESS)
        throw std::runtime_error("Failed to allocate command buffers");
}

CommandPool::~CommandPool()
{
    vkFreeCommandBuffers(m_device.GetDevice(), m_commandPool, static_cast<uint32_t>(m_commandBuffers.size()), m_commandBuffers.data());
    vkDestroyCommandPool(m_device.GetDevice(), m_commandPool, nullptr);
}

VkCommandPool CommandPool::GetCommandPool() const
{
    return m_commandPool;
}

const std::vector<VkCommandBuffer>& CommandPool::GetCommandBuffers() const
{
    return m_commandBuffers;
}
}
