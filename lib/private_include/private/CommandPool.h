#ifndef VT_COMMAND_POOL_INCLUDE_H
#define VT_COMMAND_POOL_INCLUDE_H

#include "Device.h"

namespace VT
{
class CommandPool : public NonCopyableObject
{
public:
    CommandPool(Device& device);
    ~CommandPool() override;

    Device& GetRelatedDevice() const;

    VkCommandPool GetCommandPool() const;

private:
    Device& m_device;

    VkCommandPool m_commandPool;
};
}

#endif
