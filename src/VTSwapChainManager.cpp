#include "VTSwapChainManager.h"

#include <stdexcept>

namespace VT
{
VTSwapChainManager::VTSwapChainManager(const VTPhysicalDevice& vtPhysicalDevice, const VTSurface& vtSurface)
{
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(vtPhysicalDevice.GetPhysicalDevice(), vtSurface.GetSurface(), &m_surfaceCapabilities);

    uint32_t availableSurfaceFormatCount = 0;
    vkGetPhysicalDeviceSurfaceFormatsKHR(vtPhysicalDevice.GetPhysicalDevice(), vtSurface.GetSurface(), &availableSurfaceFormatCount, nullptr);

    m_availableSurfaceFormats.resize(availableSurfaceFormatCount);
    vkGetPhysicalDeviceSurfaceFormatsKHR(vtPhysicalDevice.GetPhysicalDevice(), vtSurface.GetSurface(), &availableSurfaceFormatCount, m_availableSurfaceFormats.data());

    uint32_t availablePresentModesCount = 0;
    vkGetPhysicalDeviceSurfacePresentModesKHR(vtPhysicalDevice.GetPhysicalDevice(), vtSurface.GetSurface(), &availablePresentModesCount, nullptr);

    m_availablePresentModes.resize(availablePresentModesCount);
    vkGetPhysicalDeviceSurfacePresentModesKHR(vtPhysicalDevice.GetPhysicalDevice(), vtSurface.GetSurface(), &availablePresentModesCount, m_availablePresentModes.data());
}

VkSurfaceFormatKHR VTSwapChainManager::GetSurfaceFormat() const
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

VkPresentModeKHR VTSwapChainManager::GetPresentMode() const
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
}
