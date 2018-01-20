#include <private/Buffer.h>

namespace VT
{
Buffer::Buffer(Device& device, VkDeviceSize bufferSize, VkBufferUsageFlags bufferUsage)
    : m_device(device)
    , m_buffer(VK_NULL_HANDLE)
{
    VkBufferCreateInfo bufferInfo = {};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = bufferSize;
    bufferInfo.usage = bufferUsage;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    VkResult result = vkCreateBuffer(m_device.GetDevice(), &bufferInfo, nullptr, &m_buffer);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Failed to create buffer");

    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(m_device.GetDevice(), m_buffer, &memRequirements);
}

Buffer::~Buffer()
{
    vkDestroyBuffer(m_device.GetDevice(), m_buffer, nullptr);
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
