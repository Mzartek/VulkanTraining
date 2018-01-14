#include <private/Drawable/BaseDrawable.h>

#include <stdexcept>

namespace VT
{
BaseDrawable::BaseDrawable(CommandPool& commandPool, IGraphicsPipeline& graphicsPipeline)
    : m_commandPool(commandPool)
{
    m_commandBuffers.resize(graphicsPipeline.GetFramebuffers().size());

    VkSemaphoreCreateInfo semaphoreCreateInfo = {};
    semaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkResult result = vkCreateSemaphore(m_commandPool.GetRelatedDevice().GetDevice(), &semaphoreCreateInfo, nullptr, &m_drawSemaphore);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Failed to create draw semaphore");

    VkCommandBufferAllocateInfo allocInfo = {};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = m_commandPool.GetCommandPool();
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandBufferCount = static_cast<uint32_t>(m_commandBuffers.size());

    result = vkAllocateCommandBuffers(m_commandPool.GetRelatedDevice().GetDevice(), &allocInfo, m_commandBuffers.data());
    if (result != VK_SUCCESS)
        throw std::runtime_error("Failed to allocate command buffers");
}

BaseDrawable::~BaseDrawable()
{
    vkFreeCommandBuffers(m_commandPool.GetRelatedDevice().GetDevice(), m_commandPool.GetCommandPool(), static_cast<uint32_t>(m_commandBuffers.size()), m_commandBuffers.data());
    vkDestroySemaphore(m_commandPool.GetRelatedDevice().GetDevice(), m_drawSemaphore, nullptr);
}

CommandPool& BaseDrawable::GetRelatedCommandPool() const
{
    return m_commandPool;
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
