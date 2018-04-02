#ifndef VT_BASE_DRAWABLE_INCLUDE_H
#define VT_BASE_DRAWABLE_INCLUDE_H

#include "../Pipelines/IGraphicsPipeline.h"

namespace VT
{
class BaseDrawable : public NonCopyableObject
{
public:
    BaseDrawable(IGraphicsPipeline& graphicsPipeline);
    ~BaseDrawable() override;

    IGraphicsPipeline& GetRelatedGraphicsPipeline() const;

    VkSemaphore GetDrawSemaphore() const;

    const std::vector<VkCommandBuffer>& GetTransferCommandBuffers() const;
    const std::vector<VkCommandBuffer>& GetGraphicsCommandBuffers() const;
    const std::vector<VkCommandBuffer>& GetComputeCommandBuffers() const;

    virtual void Draw() = 0;

private:
    IGraphicsPipeline& m_graphicsPipeline;

    VkSemaphore m_drawSemaphore;

    std::vector<VkCommandBuffer> m_transferCommandBuffers;
    std::vector<VkCommandBuffer> m_graphicsCommandBuffers;
    std::vector<VkCommandBuffer> m_computeCommandBuffers;
};
}

#endif
