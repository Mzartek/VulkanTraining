#include <private/Swapchain.h>

#include <private/Managers/SwapchainManager.h>
#include <private/Managers/QueueFamiliesManager.h>

#include <array>

namespace VT
{
Swapchain::Swapchain(const Device& device)
    : m_device(device)
    , m_swapchain(VK_NULL_HANDLE)
    , m_extent({})
{
    SwapchainManager swapchainManager(m_device.GetRelatedPhysicalDevice(), m_device.GetRelatedSurface());
    QueueFamiliesManager queueFamiliesManager(m_device.GetRelatedPhysicalDevice(), m_device.GetRelatedSurface());

    VkSwapchainCreateInfoKHR createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = m_device.GetRelatedSurface().GetSurface();
    createInfo.minImageCount = swapchainManager.GetImageCount();
    createInfo.imageFormat = swapchainManager.GetSurfaceFormat().format;
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
    imageViewCreateInfo.format = swapchainManager.GetSurfaceFormat().format;
    imageViewCreateInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
    imageViewCreateInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
    imageViewCreateInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
    imageViewCreateInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
    imageViewCreateInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    imageViewCreateInfo.subresourceRange.baseMipLevel = 0;
    imageViewCreateInfo.subresourceRange.levelCount = 1;
    imageViewCreateInfo.subresourceRange.baseArrayLayer = 0;
    imageViewCreateInfo.subresourceRange.layerCount = 1;

    m_extent = swapchainManager.GetExtent2D();

    m_imageViews.resize(imageCount);
    for (uint32_t i = 0; i < imageCount; ++i)
    {
        imageViewCreateInfo.image = images[i];

        VkResult result = vkCreateImageView(m_device.GetDevice(), &imageViewCreateInfo, nullptr, &m_imageViews[i]);
        if (result != VK_SUCCESS)
            throw std::runtime_error("Failed to create image");
    }
}

Swapchain::~Swapchain()
{
    for (VkImageView imageView : m_imageViews)
        vkDestroyImageView(m_device.GetDevice(), imageView, nullptr);

    vkDestroySwapchainKHR(m_device.GetDevice(), m_swapchain, nullptr);
}

VkSwapchainKHR Swapchain::GetSwapchain()
{
    return m_swapchain;
}

VkSwapchainKHR Swapchain::GetSwapchain() const
{
    return m_swapchain;
}

const Device& Swapchain::GetRelatedDevice() const
{
    return m_device;
}

const VkExtent2D& Swapchain::GetExtent() const
{
    return m_extent;
}

const std::vector<VkImageView>& Swapchain::GetImageViews() const
{
    return m_imageViews;
}
}
