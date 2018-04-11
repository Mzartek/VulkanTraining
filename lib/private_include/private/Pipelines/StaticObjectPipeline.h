#ifndef VT_STATIC_OBJECT_PIPELINE_INCLUDE_H
#define VT_STATIC_OBJECT_PIPELINE_INCLUDE_H

#include "IGraphicsPipeline.h"

#include "../Swapchain.h"
#include "../ShadersCollector.h"

namespace VT
{
class StaticObjectPipeline : public NonCopyableObject, public IGraphicsPipeline
{
public:
    struct Matrices
    {
        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 projection;
    };

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

    VkDescriptorSetLayout GetDescriptorSetLayout() const override;
    VkPipelineLayout GetPipelineLayout() const override;
    VkRenderPass GetRenderPass() const override;
    VkPipeline GetGraphicsPipeline() const override;
    const std::vector<VkFramebuffer>& GetFramebuffers() const override;

private:
    Swapchain& m_swapchain;

    VkDescriptorSetLayout m_descriptorSetLayout;
    VkPipelineLayout m_pipelineLayout;
    VkRenderPass m_renderPass;
    VkPipeline m_graphicsPipeline;
    std::vector<VkFramebuffer> m_framebuffers;
};
}

#endif
