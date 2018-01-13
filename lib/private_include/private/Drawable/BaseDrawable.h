#ifndef VT_BASE_DRAWABLE_INCLUDE_H
#define VT_BASE_DRAWABLE_INCLUDE_H

#include "../CommandPool.h"
#include "../Pipelines/IGraphicsPipeline.h"

namespace VT
{
class BaseDrawable
{
public:
    BaseDrawable(const CommandPool& commandPool, const IGraphicsPipeline& graphicsPipeline);
    virtual ~BaseDrawable();
    BaseDrawable(const BaseDrawable& other) = delete;
    BaseDrawable(BaseDrawable&& other) = delete;
    BaseDrawable& operator=(const BaseDrawable& other) = delete;
    BaseDrawable& operator=(BaseDrawable&& other) = delete;

    const CommandPool& GetRelatedCommandPool() const;

    const std::vector<VkCommandBuffer>& GetCommandBuffers() const;

private:
    const CommandPool& m_commandPool;

    std::vector<VkCommandBuffer> m_commandBuffers;
};
}

#endif
