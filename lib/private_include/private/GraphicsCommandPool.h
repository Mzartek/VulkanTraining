#ifndef VT_GRAPHICS_COMMAND_POOL_INCLUDE_H
#define VT_GRAPHICS_COMMAND_POOL_INCLUDE_H

#include "Device.h"

namespace VT
{
class GraphicsCommandPool : public NonCopyableObject
{
public:
    GraphicsCommandPool(Device& device);
    ~GraphicsCommandPool() override;

    Device& GetRelatedDevice() const;

    VkCommandPool GetGraphicsCommandPool() const;

private:
    Device& m_device;

    VkCommandPool m_graphicsCommandPool;
};
}

#endif
