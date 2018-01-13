#ifndef VT_I_GRAPHICS_PIPELINE_HEADER_H
#define VT_I_GRAPHICS_PIPELINE_HEADER_H

#include <vulkan/vulkan.h>

#include <vector>

namespace VT
{
struct IGraphicsPipeline
{
    virtual ~IGraphicsPipeline() {}

    virtual VkPipelineLayout GetPipelineLayout() const = 0;
    virtual VkRenderPass GetRenderPass() const = 0;
    virtual VkPipeline GetGraphicsPipeline() const = 0;
    virtual const std::vector<VkFramebuffer>& GetFramebuffers() const = 0;
};
}

#endif
