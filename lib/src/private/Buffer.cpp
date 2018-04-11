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

void CreateBuffer(VT::Device& device, VkDeviceSize bufferSize, VkBufferUsageFlags bufferUsage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory)
{
    VkBufferCreateInfo bufferInfo = {};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = bufferSize;
    bufferInfo.usage = bufferUsage;

    std::array<uint32_t, 2> queueFamilyIndices =
    {
        device.GetGraphicsQueueIndex(),
        device.GetTransferQueueIndex()
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

    VkResult result = vkCreateBuffer(device.GetDevice(), &bufferInfo, nullptr, &buffer);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Failed to create buffer");

    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(device.GetDevice(), buffer, &memRequirements);

    VkMemoryAllocateInfo allocInfo = {};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = FindMemoryType(device.GetRelatedPhysicalDevice().GetPhysicalDevice(), memRequirements.memoryTypeBits, properties);

    result = vkAllocateMemory(device.GetDevice(), &allocInfo, nullptr, &bufferMemory);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Failed to allocate memory");

    result = vkBindBufferMemory(device.GetDevice(), buffer, bufferMemory, 0);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Failed to bind buffer memory");
}

void CopyBuffer(VT::Device& device, VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize bufferSize)
{
    VkCommandBufferAllocateInfo allocInfo = {};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandPool = device.GetTransferCommandPool();
    allocInfo.commandBufferCount = 1;

    VkCommandBuffer commandBuffer;
    VkResult result = vkAllocateCommandBuffers(device.GetDevice(), &allocInfo, &commandBuffer);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Failed to allocate transfer command buffers");

    VkCommandBufferBeginInfo beginInfo = {};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

    result = vkBeginCommandBuffer(commandBuffer, &beginInfo);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Failed to begin command buffer's recording");

    VkBufferCopy copyRegion = {};
    copyRegion.srcOffset = 0;
    copyRegion.dstOffset = 0;
    copyRegion.size = bufferSize;
    vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

    result = vkEndCommandBuffer(commandBuffer);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Failed to stop comand buffer's recording");

    VkSubmitInfo submitInfo = {};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffer;

    vkQueueSubmit(device.GetGraphicsQueues()[0], 1, &submitInfo, VK_NULL_HANDLE);
    vkQueueWaitIdle(device.GetGraphicsQueues()[0]);
}
}

namespace VT
{
Buffer::Buffer(Device& device, BufferType bufferType, VkDeviceSize bufferSize)
    : m_device(device)
    , m_bufferSize(bufferSize)
    , m_buffer(VK_NULL_HANDLE)
    , m_bufferMemory(VK_NULL_HANDLE)
{
    switch (bufferType)
    {
    case BufferType::Vertex:
        CreateBuffer(m_device,
            m_bufferSize,
            VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
            VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
            m_buffer,
            m_bufferMemory);
        break;
    case BufferType::Index:
        CreateBuffer(m_device,
            m_bufferSize,
            VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
            VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
            m_buffer,
            m_bufferMemory);
        break;
    case BufferType::Uniform:
        CreateBuffer(m_device,
            m_bufferSize,
            VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
            VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
            m_buffer,
            m_bufferMemory);
        break;
    default:
        throw std::runtime_error("Buffer type not supported");
    }
}

Buffer::Buffer(Device& device, BufferType bufferType, VkDeviceSize bufferSize, const void* bufferData)
    : Buffer(device, bufferType, bufferSize)
{
    UpdateData(bufferData);
}

Buffer::~Buffer()
{
    vkFreeMemory(m_device.GetDevice(), m_bufferMemory, nullptr);
    vkDestroyBuffer(m_device.GetDevice(), m_buffer, nullptr);
}

void Buffer::UpdateData(const void* bufferData)
{
    VkBuffer stagingBuffer = VK_NULL_HANDLE;
    VkDeviceMemory stagingBufferMemory = VK_NULL_HANDLE;

    CreateBuffer(m_device,
        m_bufferSize,
        VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        stagingBuffer,
        stagingBufferMemory);

    void* tmpBufferData = nullptr;
    vkMapMemory(m_device.GetDevice(), stagingBufferMemory, 0, m_bufferSize, 0, &tmpBufferData);
    std::memcpy(tmpBufferData, bufferData, static_cast<size_t>(m_bufferSize));
    vkUnmapMemory(m_device.GetDevice(), stagingBufferMemory);

    CopyBuffer(m_device, stagingBuffer, m_buffer, m_bufferSize);

    vkFreeMemory(m_device.GetDevice(), stagingBufferMemory, nullptr);
    vkDestroyBuffer(m_device.GetDevice(), stagingBuffer, nullptr);
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
