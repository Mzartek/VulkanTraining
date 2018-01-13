#include <private/Drawable/SimpleDrawable.h>

#include <private/Managers/SwapchainManager.h>

#include <stdexcept>

namespace VT
{
SimpleDrawable::SimpleDrawable(const CommandPool& commandPool, const SimplePipeline& simplePipeline)
    : BaseDrawable(commandPool, simplePipeline)
{
    SwapchainManager swapchainManager(simplePipeline.GetRelatedSwapchain().GetRelatedDevice().GetRelatedPhysicalDevice(), simplePipeline.GetRelatedSwapchain().GetRelatedDevice().GetRelatedSurface());

    const std::vector<VkCommandBuffer> commandBuffers = this->GetCommandBuffers();
    const std::vector<VkFramebuffer> framebuffers = simplePipeline.GetFramebuffers();
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
        renderPassInfo.renderPass = simplePipeline.GetRenderPass();
        renderPassInfo.framebuffer = framebuffers[i];
        renderPassInfo.renderArea.offset = {0, 0};
        renderPassInfo.renderArea.extent = swapchainManager.GetExtent2D();

        VkClearValue clearColor = {0.0f, 0.0f, 0.0f, 1.0f};
        renderPassInfo.clearValueCount = 1;
        renderPassInfo.pClearValues = &clearColor;

        vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

        vkCmdBindPipeline(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, simplePipeline.GetGraphicsPipeline());

        vkCmdSetViewport(commandBuffers[i], 0, 1, &simplePipeline.GetViewport());

        vkCmdDraw(commandBuffers[i], 3, 1, 0, 0);

        vkCmdEndRenderPass(commandBuffers[i]);

        result = vkEndCommandBuffer(commandBuffers[i]);
        if (result != VK_SUCCESS)
            throw std::runtime_error("Failed to stop comannd buffer's recording");
    }
}
}
