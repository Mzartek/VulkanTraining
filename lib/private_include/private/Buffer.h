#ifndef VT_BUFFER_INCLUDE_H
#define VT_BUFFER_INCLUDE_H

#include "Device.h"

namespace VT
{
class Buffer : public NonCopyableObject
{
public:
    Buffer(Device& device, VkDeviceSize bufferSize, VkBufferUsageFlags bufferUsage, VkMemoryPropertyFlags properties);
    ~Buffer() override;

    Device& GetRelatedDevice() const;

    VkBuffer GetBuffer() const;
    VkDeviceMemory GetBufferMemory() const;

private:
    Device &m_device;

    VkBuffer m_buffer;
    VkDeviceMemory m_bufferMemory;
};
}

#endif
