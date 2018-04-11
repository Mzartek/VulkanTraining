#include <private/Drawables/BaseDrawable.h>

namespace VT
{
BaseDrawable::BaseDrawable(IGraphicsPipeline& graphicsPipeline)
    : m_graphicsPipeline(graphicsPipeline)
{
    m_transferCommandBuffers.resize(m_graphicsPipeline.GetFramebuffers().size());
    m_graphicsCommandBuffers.resize(m_graphicsPipeline.GetFramebuffers().size());
    m_computeCommandBuffers.resize(m_graphicsPipeline.GetFramebuffers().size());

    VkSemaphoreCreateInfo semaphoreCreateInfo = {};
    semaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkResult result = vkCreateSemaphore(m_graphicsPipeline.GetRelatedDevice().GetDevice(), &semaphoreCreateInfo, nullptr, &m_drawSemaphore);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Failed to create draw semaphore");

    VkCommandBufferAllocateInfo allocInfo = {};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandBufferCount = static_cast<uint32_t>(m_transferCommandBuffers.size());
    allocInfo.commandPool = m_graphicsPipeline.GetRelatedDevice().GetTransferCommandPool();

    result = vkAllocateCommandBuffers(m_graphicsPipeline.GetRelatedDevice().GetDevice(), &allocInfo, m_transferCommandBuffers.data());
    if (result != VK_SUCCESS)
        throw std::runtime_error("Failed to allocate transfer command buffers");

    allocInfo.commandBufferCount = static_cast<uint32_t>(m_graphicsCommandBuffers.size());
    allocInfo.commandPool = m_graphicsPipeline.GetRelatedDevice().GetGraphicsCommandPool();

    result = vkAllocateCommandBuffers(m_graphicsPipeline.GetRelatedDevice().GetDevice(), &allocInfo, m_graphicsCommandBuffers.data());
    if (result != VK_SUCCESS)
        throw std::runtime_error("Failed to allocate graphics command buffers");

    allocInfo.commandBufferCount = static_cast<uint32_t>(m_computeCommandBuffers.size());
    allocInfo.commandPool = m_graphicsPipeline.GetRelatedDevice().GetComputeCommandPool();

    result = vkAllocateCommandBuffers(m_graphicsPipeline.GetRelatedDevice().GetDevice(), &allocInfo, m_computeCommandBuffers.data());
    if (result != VK_SUCCESS)
        throw std::runtime_error("Failed to allocate compute command buffers");
}

BaseDrawable::~BaseDrawable()
{
    vkFreeCommandBuffers(m_graphicsPipeline.GetRelatedDevice().GetDevice(), m_graphicsPipeline.GetRelatedDevice().GetComputeCommandPool(), static_cast<uint32_t>(m_computeCommandBuffers.size()), m_computeCommandBuffers.data());
    vkFreeCommandBuffers(m_graphicsPipeline.GetRelatedDevice().GetDevice(), m_graphicsPipeline.GetRelatedDevice().GetGraphicsCommandPool(), static_cast<uint32_t>(m_graphicsCommandBuffers.size()), m_graphicsCommandBuffers.data());
    vkFreeCommandBuffers(m_graphicsPipeline.GetRelatedDevice().GetDevice(), m_graphicsPipeline.GetRelatedDevice().GetTransferCommandPool(), static_cast<uint32_t>(m_transferCommandBuffers.size()), m_transferCommandBuffers.data());
    vkDestroySemaphore(m_graphicsPipeline.GetRelatedDevice().GetDevice(), m_drawSemaphore, nullptr);
}

IGraphicsPipeline& BaseDrawable::GetRelatedGraphicsPipeline() const
{
    return m_graphicsPipeline;
}

VkSemaphore BaseDrawable::GetDrawSemaphore() const
{
    return m_drawSemaphore;
}

const std::vector<VkCommandBuffer>& BaseDrawable::GetTransferCommandBuffers() const
{
    return m_transferCommandBuffers;
}

const std::vector<VkCommandBuffer>& BaseDrawable::GetGraphicsCommandBuffers() const
{
    return m_graphicsCommandBuffers;
}

const std::vector<VkCommandBuffer>& BaseDrawable::GetComputeCommandBuffers() const
{
    return m_computeCommandBuffers;
}
}
