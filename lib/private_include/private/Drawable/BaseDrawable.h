#ifndef VT_BASE_DRAWABLE_INCLUDE_H
#define VT_BASE_DRAWABLE_INCLUDE_H

#include "../CommandPool.h"
#include "../Pipelines/IGraphicsPipeline.h"

namespace VT
{
class BaseDrawable : public NonCopyableObject
{
public:
    BaseDrawable(CommandPool& commandPool, IGraphicsPipeline& graphicsPipeline);
    ~BaseDrawable() override;

    CommandPool& GetRelatedCommandPool() const;

    VkSemaphore GetDrawSemaphore() const;
    const std::vector<VkCommandBuffer>& GetCommandBuffers() const;

    virtual void Draw() = 0;

private:
    CommandPool& m_commandPool;

    VkSemaphore m_drawSemaphore;
    std::vector<VkCommandBuffer> m_commandBuffers;
};
}

#endif
