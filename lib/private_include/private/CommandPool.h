#ifndef VT_COMMAND_POOL_INCLUDE_H
#define VT_COMMAND_POOL_INCLUDE_H

#include "Device.h"
#include "Pipelines/IGraphicsPipeline.h"

namespace VT
{
class CommandPool
{
public:
    CommandPool(const Device& device, const IGraphicsPipeline& graphicsPipeline);
    virtual ~CommandPool();
    CommandPool(const CommandPool& other) = delete;
    CommandPool(CommandPool&& other) = delete;
    CommandPool& operator=(const CommandPool& other) = delete;
    CommandPool& operator=(CommandPool&& other) = delete;

    VkCommandPool GetCommandPool() const;
    const std::vector<VkCommandBuffer>& GetCommandBuffers() const;

private:
    const Device& m_device;

    VkCommandPool m_commandPool;
    std::vector<VkCommandBuffer> m_commandBuffers;
};
}

#endif
