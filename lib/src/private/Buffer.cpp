#include <private/Buffer.h>

namespace VT
{
Buffer::Buffer(Device& device)
    : m_device(device)
    , m_buffer(VK_NULL_HANDLE)
{
}

Buffer::~Buffer()
{
}

Device& Buffer::GetRelatedDevice() const
{
    return m_device;
}

VkBuffer Buffer::GetBuffer() const
{
    return m_buffer;
}
}
