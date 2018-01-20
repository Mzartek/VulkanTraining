#ifndef VT_SIMPLE_PIPELINE_INCLUDE_H
#define VT_SIMPLE_PIPELINE_INCLUDE_H

#include "IGraphicsPipeline.h"

#include "../Swapchain.h"
#include "../Shader.h"

namespace VT
{
class SimplePipeline : public NonCopyableObject, public IGraphicsPipeline
{
public:
    SimplePipeline(Swapchain& swapchain, const std::string& shadersPath);
    ~SimplePipeline() override;

    Swapchain& GetRelatedSwapchain() const;

    const VkViewport& GetViewport() const;

    VkPipelineLayout GetPipelineLayout() const override;
    VkRenderPass GetRenderPass() const override;
    VkPipeline GetGraphicsPipeline() const override;
    const std::vector<VkFramebuffer>& GetFramebuffers() const override;

private:
    Swapchain& m_swapchain;

    Shader m_vertexShader;
    Shader m_fragmentShader;

    VkViewport m_viewport;

    VkPipelineLayout m_pipelineLayout;
    VkRenderPass m_renderPass;
    VkPipeline m_graphicsPipeline;
    std::vector<VkFramebuffer> m_framebuffers;
};
}

#endif
