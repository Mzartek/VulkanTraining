#ifndef VT_SWAPCHAIN_MANAGER_INCLUDE_H
#define VT_SWAPCHAIN_MANAGER_INCLUDE_H

#include "../PhysicalDevice.h"
#include "../Surface.h"

namespace VT
{
class SwapchainManager
{
public:
    SwapchainManager(const PhysicalDevice& physicalDevice, const Surface& surface);
    virtual ~SwapchainManager() = default;

    VkSurfaceCapabilitiesKHR GetSurfaceCapabilities() const;
    VkSurfaceFormatKHR GetSurfaceFormat() const;
    VkPresentModeKHR GetPresentMode() const;
    VkExtent2D GetExtent2D() const;
    uint32_t GetImageCount() const;

private:
    const Surface& m_surface;

    VkSurfaceCapabilitiesKHR m_surfaceCapabilities;
    std::vector<VkSurfaceFormatKHR> m_availableSurfaceFormats;
    std::vector<VkPresentModeKHR> m_availablePresentModes;
};
}

#endif // VT_SWAP_CHAIN_MANAGER_INCLUDE_H
