#include <private/Drawable/SimpleDrawable.h>

#include <private/Managers/SwapchainManager.h>

#include <stdexcept>

namespace VT
{
SimpleDrawable::SimpleDrawable(CommandPool& commandPool, SimplePipeline& simplePipeline)
    : BaseDrawable(commandPool, simplePipeline)
    , m_simplePipeline(simplePipeline)
{
    const PhysicalDevice& physicalDevice = m_simplePipeline.GetRelatedSwapchain().GetRelatedDevice().GetRelatedPhysicalDevice();
    const Surface& surface = m_simplePipeline.GetRelatedSwapchain().GetRelatedDevice().GetRelatedSurface();
    SwapchainManager swapchainManager(physicalDevice, surface);

    const std::vector<VkCommandBuffer> commandBuffers = this->GetCommandBuffers();
    const std::vector<VkFramebuffer> framebuffers = m_simplePipeline.GetFramebuffers();
    for (size_t i = 0; i < commandBuffers.size(); ++i)
    {
        VkCommandBufferBeginInfo beginInfo = {};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
        beginInfo.pInheritanceInfo = nullptr;

        VkResult result = vkBeginCommandBuffer(commandBuffers[i], &beginInfo);
        if (result != VK_SUCCESS)
            throw std::runtime_error("Failed to begin command buffer's recording");

        VkRenderPassBeginInfo renderPassInfo = {};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass = m_simplePipeline.GetRenderPass();
        renderPassInfo.framebuffer = framebuffers[i];
        renderPassInfo.renderArea.offset = {0, 0};
        renderPassInfo.renderArea.extent = swapchainManager.GetExtent2D();

        VkClearValue clearColor = {0.0f, 0.0f, 0.0f, 1.0f};
        renderPassInfo.clearValueCount = 1;
        renderPassInfo.pClearValues = &clearColor;

        vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

        vkCmdBindPipeline(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, m_simplePipeline.GetGraphicsPipeline());

        vkCmdSetViewport(commandBuffers[i], 0, 1, &m_simplePipeline.GetViewport());

        vkCmdDraw(commandBuffers[i], 3, 1, 0, 0);

        vkCmdEndRenderPass(commandBuffers[i]);

        result = vkEndCommandBuffer(commandBuffers[i]);
        if (result != VK_SUCCESS)
            throw std::runtime_error("Failed to stop comannd buffer's recording");
    }
}

void SimpleDrawable::Draw()
{
    const Device& device = m_simplePipeline.GetRelatedSwapchain().GetRelatedDevice();
    Swapchain& swapchain = m_simplePipeline.GetRelatedSwapchain();

    VkQueue graphicsQueue = device.GetGraphicsQueues()[0];

    const uint32_t imageIndex = swapchain.GetCurrentImageViewIndex();
    const std::vector<VkCommandBuffer> commandBuffers = this->GetCommandBuffers();

    VkSemaphore waitSemaphores[] = { swapchain.GetSemaphores()[swapchain.GetCurrentSemaphoreIndex()] };
    VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
    VkSemaphore signalSemaphores[] = { this->GetDrawSemaphore() };

    VkSubmitInfo submitInfo = {};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pWaitDstStageMask = waitStages;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffers[imageIndex];
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signalSemaphores;

    VkResult result = vkQueueSubmit(graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Failed to submit info for graphics queue");

    swapchain.RegisterSemaphoreToWait(this->GetDrawSemaphore());
}
}
