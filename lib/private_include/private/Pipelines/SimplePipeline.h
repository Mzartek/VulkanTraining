#ifndef VT_SIMPLE_PIPELINE_INCLUDE_H
#define VT_SIMPLE_PIPELINE_INCLUDE_H

#include "IGraphicsPipeline.h"

#include "../Swapchain.h"
#include "../Shader.h"

namespace VT
{
class SimplePipeline : public IGraphicsPipeline
{
public:
    SimplePipeline(const Swapchain& swapchain, const std::string& shadersPath);
    ~SimplePipeline() override;
    SimplePipeline(const SimplePipeline& other) = delete;
    SimplePipeline(SimplePipeline&& other) = delete;
    SimplePipeline& operator=(const SimplePipeline& other) = delete;
    SimplePipeline& operator=(SimplePipeline&& other) = delete;

    VkPipelineLayout GetPipelineLayout() const override;
    VkRenderPass GetRenderPass() const override;
    VkPipeline GetGraphicsPipeline() const override;
    const std::vector<VkFramebuffer>& GetFramebuffers() const override;

private:
    const Swapchain& m_swapchain;

    Shader m_vertexShader;
    Shader m_fragmentShader;

    VkPipelineLayout m_pipelineLayout;
    VkRenderPass m_renderPass;
    VkPipeline m_graphicsPipeline;
    std::vector<VkFramebuffer> m_framebuffers;
};
}

#endif
