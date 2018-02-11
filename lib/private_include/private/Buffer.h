#ifndef VT_BUFFER_INCLUDE_H
#define VT_BUFFER_INCLUDE_H

#include "Device.h"

namespace VT
{
enum class BufferType { Vertex, Index, Uniform };

class Buffer : public NonCopyableObject
{
public:
    Buffer(Device& device, BufferType bufferType, const void* bufferData, VkDeviceSize bufferSize);
    ~Buffer() override;

    Device& GetRelatedDevice() const;

    VkBuffer GetBuffer() const;
    VkDeviceMemory GetBufferMemory() const;

private:
    Device& m_device;

    VkBuffer m_buffer;
    VkDeviceMemory m_bufferMemory;
};
}

#endif
