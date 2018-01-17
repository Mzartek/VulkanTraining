#include <private/Swapchain.h>

#include <private/Managers/SwapchainManager.h>
#include <private/Managers/QueueFamiliesManager.h>

#include <array>

namespace VT
{
Swapchain::Swapchain(Device& device)
    : m_device(device)
    , m_extend2D({})
    , m_format(VK_FORMAT_UNDEFINED)
    , m_swapchain(VK_NULL_HANDLE)
    , m_currentImageViewIndex(0)
    , m_currentSemaphoreIndex(0)
    , m_nextSemaphoreIndex(0)
{
    SwapchainManager swapchainManager(m_device.GetRelatedPhysicalDevice(), m_device.GetRelatedSurface());
    QueueFamiliesManager queueFamiliesManager(m_device.GetRelatedPhysicalDevice(), m_device.GetRelatedSurface());

    m_extend2D = swapchainManager.GetExtent2D();
    m_format = swapchainManager.GetSurfaceFormat().format;

    VkSwapchainCreateInfoKHR createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = m_device.GetRelatedSurface().GetSurface();
    createInfo.minImageCount = swapchainManager.GetImageCount();
    createInfo.imageFormat = m_format;
    createInfo.imageColorSpace = swapchainManager.GetSurfaceFormat().colorSpace;
    createInfo.imageExtent = swapchainManager.GetExtent2D();
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    std::array<uint32_t, 2> queueFamilyIndices =
    {
        queueFamiliesManager.GetGraphicsQueueIndex(),
        queueFamiliesManager.GetPresentQueueIndex()
    };

    if (queueFamilyIndices[0] != queueFamilyIndices[1])
    {
        createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        createInfo.queueFamilyIndexCount = static_cast<uint32_t>(queueFamilyIndices.size());
        createInfo.pQueueFamilyIndices = queueFamilyIndices.data();
    }
    else
    {
        createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        createInfo.queueFamilyIndexCount = 0;
        createInfo.pQueueFamilyIndices = nullptr;
    }

    createInfo.preTransform = swapchainManager.GetSurfaceCapabilities().currentTransform;
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    createInfo.presentMode = swapchainManager.GetPresentMode();
    createInfo.clipped = VK_TRUE;
    createInfo.oldSwapchain = VK_NULL_HANDLE;

    VkResult result = vkCreateSwapchainKHR(m_device.GetDevice(), &createInfo, nullptr, &m_swapchain);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Failed to create swapchain");

    uint32_t imageCount = 0;
    vkGetSwapchainImagesKHR(m_device.GetDevice(), m_swapchain, &imageCount, nullptr);

    std::vector<VkImage> images(imageCount);
    vkGetSwapchainImagesKHR(m_device.GetDevice(), m_swapchain, &imageCount, images.data());

    VkImageViewCreateInfo imageViewCreateInfo = {};
    imageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    imageViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    imageViewCreateInfo.format = m_format;
    imageViewCreateInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
    imageViewCreateInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
    imageViewCreateInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
    imageViewCreateInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
    imageViewCreateInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    imageViewCreateInfo.subresourceRange.baseMipLevel = 0;
    imageViewCreateInfo.subresourceRange.levelCount = 1;
    imageViewCreateInfo.subresourceRange.baseArrayLayer = 0;
    imageViewCreateInfo.subresourceRange.layerCount = 1;

    VkSemaphoreCreateInfo semaphoreCreateInfo = {};
    semaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    m_imageViews.resize(imageCount);
    m_semaphores.resize(imageCount);
    for (uint32_t i = 0; i < imageCount; ++i)
    {
        imageViewCreateInfo.image = images[i];

        result = vkCreateImageView(m_device.GetDevice(), &imageViewCreateInfo, nullptr, &m_imageViews[i]);
        if (result != VK_SUCCESS)
            throw std::runtime_error("Failed to create image");

        result = vkCreateSemaphore(m_device.GetDevice(), &semaphoreCreateInfo, nullptr, &m_semaphores[i]);
        if (result != VK_SUCCESS)
            throw std::runtime_error("Failed to create semaphore");
    }
}

Swapchain::~Swapchain()
{
    for (VkSemaphore semaphore : m_semaphores)
        vkDestroySemaphore(m_device.GetDevice(), semaphore, nullptr);
    for (VkImageView imageView : m_imageViews)
        vkDestroyImageView(m_device.GetDevice(), imageView, nullptr);

    vkDestroySwapchainKHR(m_device.GetDevice(), m_swapchain, nullptr);
}

Device& Swapchain::GetRelatedDevice() const
{
    return m_device;
}

const VkExtent2D& Swapchain::GetExtent2D() const
{
    return m_extend2D;
}

VkFormat Swapchain::GetFormat() const
{
    return m_format;
}

VkSwapchainKHR Swapchain::GetSwapchain() const
{
    return m_swapchain;
}

const std::vector<VkImageView>& Swapchain::GetImageViews() const
{
    return m_imageViews;
}

const std::vector<VkSemaphore>& Swapchain::GetSemaphores() const
{
    return m_semaphores;
}

void Swapchain::LoadNextImage()
{
    m_currentSemaphoreIndex = m_nextSemaphoreIndex;

    VkResult result = vkAcquireNextImageKHR(
        m_device.GetDevice(),
        m_swapchain,
        std::numeric_limits<uint64_t>::max(),
        m_semaphores[m_currentSemaphoreIndex],
        VK_NULL_HANDLE,
        &m_currentImageViewIndex);

    if (result == VK_ERROR_OUT_OF_DATE_KHR)
        throw SwapchainOutOfDateException();

    if (result != VK_SUCCESS)
        throw std::runtime_error("Failed to acquire next swapchain's image");

    m_nextSemaphoreIndex++;
    m_nextSemaphoreIndex %= m_imageViews.size();
}

void Swapchain::RegisterSemaphoreToWait(VkSemaphore semaphoreToWait)
{
    m_registeredSemaphoresToWait.push_back(semaphoreToWait);
}

void Swapchain::PresentImage()
{
    VkQueue presentQueue = m_device.GetPresentQueues()[0];

    VkPresentInfoKHR presentInfo = {};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    presentInfo.waitSemaphoreCount = static_cast<uint32_t>(m_registeredSemaphoresToWait.size());
    presentInfo.pWaitSemaphores = m_registeredSemaphoresToWait.data();
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = &m_swapchain;
    presentInfo.pImageIndices = &m_currentImageViewIndex;

    VkResult result = vkQueuePresentKHR(presentQueue, &presentInfo);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Failed to submit info for present queue");

    m_registeredSemaphoresToWait.clear();
}

uint32_t Swapchain::GetCurrentImageViewIndex() const
{
    return m_currentImageViewIndex;
}

uint32_t Swapchain::GetCurrentSemaphoreIndex() const
{
    return m_currentSemaphoreIndex;
}
}
