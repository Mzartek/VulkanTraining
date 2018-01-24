#ifndef VT_STATIC_OBJECT_PIPELINE_INCLUDE_H
#define VT_STATIC_OBJECT_PIPELINE_INCLUDE_H

#include "IGraphicsPipeline.h"

#include "../Swapchain.h"
#include "../Shader.h"

#include <glm/glm.hpp>

namespace VT
{
class StaticObjectPipeline : public NonCopyableObject, public IGraphicsPipeline
{
public:
    struct Vertex
    {
        glm::vec3 position;
        glm::vec2 texCoord;
    };

    StaticObjectPipeline(Swapchain& swapchain, const std::string& shadersPath);
    ~StaticObjectPipeline() override;

    Swapchain& GetRelatedSwapchain() const;

    const VkViewport& GetViewport() const;

    Device& GetRelatedDevice() const override;

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
