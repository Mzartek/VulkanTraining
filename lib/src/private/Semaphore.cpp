#include <private/Semaphore.h>

#include <stdexcept>

namespace VT
{
Semaphore::Semaphore(const Device& device)
    : m_device(device)
{
    VkSemaphoreCreateInfo semaphoreInfo = {};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkResult result = vkCreateSemaphore(m_device.GetDevice(), &semaphoreInfo, nullptr, &m_semaphore);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Failed to create semaphore");
}

Semaphore::~Semaphore()
{
    vkDestroySemaphore(m_device.GetDevice(), m_semaphore, nullptr);
}

const Device& Semaphore::GetRelatedDevice() const
{
    return m_device;
}

VkSemaphore Semaphore::GetSemaphore() const
{
    return m_semaphore;
}
}
