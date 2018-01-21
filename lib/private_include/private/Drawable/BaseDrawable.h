#ifndef VT_BASE_DRAWABLE_INCLUDE_H
#define VT_BASE_DRAWABLE_INCLUDE_H

#include "../GraphicsCommandPool.h"
#include "../Pipelines/IGraphicsPipeline.h"

namespace VT
{
class BaseDrawable : public NonCopyableObject
{
public:
    BaseDrawable(GraphicsCommandPool& graphicsCommandPool, IGraphicsPipeline& graphicsPipeline);
    ~BaseDrawable() override;

    GraphicsCommandPool& GetRelatedGraphicsCommandPool() const;

    VkSemaphore GetDrawSemaphore() const;
    const std::vector<VkCommandBuffer>& GetCommandBuffers() const;

    virtual void Draw() = 0;

private:
    GraphicsCommandPool& m_graphicsCommandPool;

    VkSemaphore m_drawSemaphore;
    std::vector<VkCommandBuffer> m_commandBuffers;
};
}

#endif
