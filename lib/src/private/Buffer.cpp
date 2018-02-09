#include <private/Buffer.h>

namespace
{
uint32_t FindMemoryType(VkPhysicalDevice physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties)
{
    VkPhysicalDeviceMemoryProperties memProperties;
    vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);

    bool found = false;
    uint32_t memoryType = 0;
    for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++)
    {
        if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties)
        {
            found = true;
            memoryType = i;
            break;
        }
    }

    if (!found)
        throw std::runtime_error("Failed to find suitable memory type");

    return memoryType;
}
}

namespace VT
{
Buffer::Buffer(Device& device, VkDeviceSize bufferSize, VkBufferUsageFlags bufferUsage, VkMemoryPropertyFlags properties)
    : m_device(device)
    , m_buffer(VK_NULL_HANDLE)
    , m_bufferMemory(VK_NULL_HANDLE)
{
    VkBufferCreateInfo bufferInfo = {};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = bufferSize;
    bufferInfo.usage = bufferUsage;

    std::array<uint32_t, 2> queueFamilyIndices =
    {
        m_device.GetGraphicsQueueIndex(),
        m_device.GetTransferQueueIndex()
    };

    if (queueFamilyIndices[0] != queueFamilyIndices[1])
    {
        bufferInfo.sharingMode = VK_SHARING_MODE_CONCURRENT;
        bufferInfo.queueFamilyIndexCount = static_cast<uint32_t>(queueFamilyIndices.size());
        bufferInfo.pQueueFamilyIndices = queueFamilyIndices.data();
    }
    else
    {
        bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        bufferInfo.queueFamilyIndexCount = 0;
        bufferInfo.pQueueFamilyIndices = nullptr;
    }

    VkResult result = vkCreateBuffer(m_device.GetDevice(), &bufferInfo, nullptr, &m_buffer);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Failed to create buffer");

    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(m_device.GetDevice(), m_buffer, &memRequirements);

    VkMemoryAllocateInfo allocInfo = {};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = FindMemoryType(device.GetRelatedPhysicalDevice().GetPhysicalDevice(), memRequirements.memoryTypeBits, properties);

    result = vkAllocateMemory(m_device.GetDevice(), &allocInfo, nullptr, &m_bufferMemory);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Failed to allocate memory");

    vkBindBufferMemory(m_device.GetDevice(), m_buffer, m_bufferMemory, 0);
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

VkDeviceMemory Buffer::GetBufferMemory() const
{
    return m_bufferMemory;
}
}
