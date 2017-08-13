#include "VTSwapchain.h"

#include "VTSwapchainManager.h"
#include "VTQueueFamiliesManager.h"

#include <array>

namespace VT
{
VTSwapchain::VTSwapchain(const VTDevice& vtDevice)
    : m_device(vtDevice)
    , m_swapchain(VK_NULL_HANDLE)
{
    VTSwapchainManager swapchainManager(m_device.GetRelatedPhysicalDevice(), m_device.GetRelatedSurface());
    VTQueueFamiliesManager queueFamiliesManager(m_device.GetRelatedPhysicalDevice(), m_device.GetRelatedSurface());

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

    m_images.resize(imageCount);
    vkGetSwapchainImagesKHR(m_device.GetDevice(), m_swapchain, &imageCount, m_images.data());
}

VTSwapchain::~VTSwapchain()
{
    vkDestroySwapchainKHR(m_device.GetDevice(), m_swapchain, nullptr);
}

VkSwapchainKHR VTSwapchain::GetSwapchain()
{
    return m_swapchain;
}

VkSwapchainKHR VTSwapchain::GetSwapchain() const
{
    return m_swapchain;
}

const std::vector<VkImage>& VTSwapchain::GetImages() const
{
    return m_images;
}
}