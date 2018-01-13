#ifndef VT_COMMAND_POOL_INCLUDE_H
#define VT_COMMAND_POOL_INCLUDE_H

#include "Device.h"

namespace VT
{
class CommandPool
{
public:
    CommandPool(const Device& device);
    virtual ~CommandPool();
    CommandPool(const CommandPool& other) = delete;
    CommandPool(CommandPool&& other) = delete;
    CommandPool& operator=(const CommandPool& other) = delete;
    CommandPool& operator=(CommandPool&& other) = delete;

    const Device& GetRelatedDevice() const;

    VkCommandPool GetCommandPool() const;

private:
    const Device& m_device;

    VkCommandPool m_commandPool;
};
}

#endif
