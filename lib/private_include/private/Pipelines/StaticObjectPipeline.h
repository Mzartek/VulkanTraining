#ifndef VT_STATIC_OBJECT_PIPELINE_INCLUDE_H
#define VT_STATIC_OBJECT_PIPELINE_INCLUDE_H

#include "IGraphicsPipeline.h"

#include "../Swapchain.h"
#include "../ShadersCollector.h"

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

    using Index = uint32_t;

    StaticObjectPipeline(Swapchain& swapchain, const ShadersCollector& shadersCollector);
    ~StaticObjectPipeline() override;

    Swapchain& GetRelatedSwapchain() const;

    Device& GetRelatedDevice() const override;

    VkPipelineLayout GetPipelineLayout() const override;
    VkRenderPass GetRenderPass() const override;
    VkPipeline GetGraphicsPipeline() const override;
    const std::vector<VkFramebuffer>& GetFramebuffers() const override;

private:
    Swapchain& m_swapchain;

    VkPipelineLayout m_pipelineLayout;
    VkRenderPass m_renderPass;
    VkPipeline m_graphicsPipeline;
    std::vector<VkFramebuffer> m_framebuffers;
};
}

#endif
