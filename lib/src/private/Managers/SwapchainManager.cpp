#include <private/Managers/SwapchainManager.h>

#include <stdexcept>
#include <limits>
#include <algorithm>

namespace VT
{
SwapchainManager::SwapchainManager(const PhysicalDevice& physicalDevice, const Surface& surface)
    : m_surface(surface)
{
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice.GetPhysicalDevice(), surface.GetSurface(), &m_surfaceCapabilities);

    uint32_t availableSurfaceFormatCount = 0;
    vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice.GetPhysicalDevice(), surface.GetSurface(), &availableSurfaceFormatCount, nullptr);

    m_availableSurfaceFormats.resize(availableSurfaceFormatCount);
    vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice.GetPhysicalDevice(), surface.GetSurface(), &availableSurfaceFormatCount, m_availableSurfaceFormats.data());

    uint32_t availablePresentModesCount = 0;
    vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice.GetPhysicalDevice(), surface.GetSurface(), &availablePresentModesCount, nullptr);

    m_availablePresentModes.resize(availablePresentModesCount);
    vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice.GetPhysicalDevice(), surface.GetSurface(), &availablePresentModesCount, m_availablePresentModes.data());
}

VkSurfaceCapabilitiesKHR SwapchainManager::GetSurfaceCapabilities() const
{
    return m_surfaceCapabilities;
}

VkSurfaceFormatKHR SwapchainManager::GetSurfaceFormat() const
{
    if (m_availableSurfaceFormats.empty())
        throw std::runtime_error("No available surface formats");

    VkSurfaceFormatKHR surfaceFormat = m_availableSurfaceFormats.front();

    if (m_availableSurfaceFormats.size() == 1 && m_availableSurfaceFormats.front().format == VK_FORMAT_UNDEFINED)
    {
        surfaceFormat.format = VK_FORMAT_B8G8R8A8_UNORM;
        surfaceFormat.colorSpace = VK_COLORSPACE_SRGB_NONLINEAR_KHR;
        return surfaceFormat;
    }

    for (const auto& availableSurfaceFormat: m_availableSurfaceFormats)
        if (availableSurfaceFormat.format == VK_FORMAT_B8G8R8A8_UNORM && availableSurfaceFormat.colorSpace == VK_COLORSPACE_SRGB_NONLINEAR_KHR)
            return availableSurfaceFormat;

    return surfaceFormat;
}

VkPresentModeKHR SwapchainManager::GetPresentMode() const
{
    if (m_availablePresentModes.empty())
        throw std::runtime_error("No available present modes");

    VkPresentModeKHR presentMode = m_availablePresentModes.front();

    for (const auto& availablePresentMode : m_availablePresentModes)
        if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
            return availablePresentMode;
        else if (availablePresentMode == VK_PRESENT_MODE_IMMEDIATE_KHR)
            presentMode = availablePresentMode;

    return presentMode;
}

VkExtent2D SwapchainManager::GetExtent2D() const
{
    if (m_surfaceCapabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
        return m_surfaceCapabilities.currentExtent;

    uint32_t windowWidth = m_surface.GetRelatedWindow().GetWidth();
    uint32_t windowHeight = m_surface.GetRelatedWindow().GetHeight();

    VkExtent2D extent2D;
    extent2D.width = std::max(m_surfaceCapabilities.minImageExtent.width, std::min(m_surfaceCapabilities.maxImageExtent.width, windowWidth));
    extent2D.height = std::max(m_surfaceCapabilities.minImageExtent.height, std::min(m_surfaceCapabilities.maxImageExtent.height, windowHeight));

    return extent2D;
}

uint32_t SwapchainManager::GetImageCount() const
{
    uint32_t imageCount = m_surfaceCapabilities.minImageCount + 1;

    if (m_surfaceCapabilities.maxImageCount > 0 && imageCount > m_surfaceCapabilities.maxImageCount)
        return m_surfaceCapabilities.maxImageCount;

    return imageCount;
}
}
