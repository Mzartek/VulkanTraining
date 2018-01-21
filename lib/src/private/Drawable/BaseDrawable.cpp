#include <private/Drawable/BaseDrawable.h>

#include <stdexcept>

namespace VT
{
BaseDrawable::BaseDrawable(GraphicsCommandPool& graphicsCommandPool, IGraphicsPipeline& graphicsPipeline)
    : m_graphicsCommandPool(graphicsCommandPool)
{
    m_commandBuffers.resize(graphicsPipeline.GetFramebuffers().size());

    VkSemaphoreCreateInfo semaphoreCreateInfo = {};
    semaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkResult result = vkCreateSemaphore(m_graphicsCommandPool.GetRelatedDevice().GetDevice(), &semaphoreCreateInfo, nullptr, &m_drawSemaphore);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Failed to create draw semaphore");

    VkCommandBufferAllocateInfo allocInfo = {};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = m_graphicsCommandPool.GetGraphicsCommandPool();
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandBufferCount = static_cast<uint32_t>(m_commandBuffers.size());

    result = vkAllocateCommandBuffers(m_graphicsCommandPool.GetRelatedDevice().GetDevice(), &allocInfo, m_commandBuffers.data());
    if (result != VK_SUCCESS)
        throw std::runtime_error("Failed to allocate command buffers");
}

BaseDrawable::~BaseDrawable()
{
    vkFreeCommandBuffers(m_graphicsCommandPool.GetRelatedDevice().GetDevice(), m_graphicsCommandPool.GetGraphicsCommandPool(), static_cast<uint32_t>(m_commandBuffers.size()), m_commandBuffers.data());
    vkDestroySemaphore(m_graphicsCommandPool.GetRelatedDevice().GetDevice(), m_drawSemaphore, nullptr);
}

GraphicsCommandPool& BaseDrawable::GetRelatedGraphicsCommandPool() const
{
    return m_graphicsCommandPool;
}

VkSemaphore BaseDrawable::GetDrawSemaphore() const
{
    return m_drawSemaphore;
}

const std::vector<VkCommandBuffer>& BaseDrawable::GetCommandBuffers() const
{
    return m_commandBuffers;
}
}
