#ifndef VT_SWAPCHAIN_MANAGER_INCLUDE_H
#define VT_SWAPCHAIN_MANAGER_INCLUDE_H

#include "VTPhysicalDevice.h"
#include "VTSurface.h"

namespace VT
{
class VTSwapchainManager
{
public:
    VTSwapchainManager(const VTPhysicalDevice& vtPhysicalDevice, const VTSurface& vtSurface);
    virtual ~VTSwapchainManager() = default;
    VTSwapchainManager(const VTSwapchainManager& other) = delete;
    VTSwapchainManager(VTSwapchainManager&& other) = delete;
    VTSwapchainManager& operator=(const VTSwapchainManager& other) = delete;
    VTSwapchainManager& operator=(VTSwapchainManager&& other) = delete;

    VkSurfaceCapabilitiesKHR GetSurfaceCapabilities() const;
    VkSurfaceFormatKHR GetSurfaceFormat() const;
    VkPresentModeKHR GetPresentMode() const;
    VkExtent2D GetExtent2D() const;
    uint32_t GetImageCount() const;

private:
    const VTSurface& m_surface;

    VkSurfaceCapabilitiesKHR m_surfaceCapabilities;
    std::vector<VkSurfaceFormatKHR> m_availableSurfaceFormats;
    std::vector<VkPresentModeKHR> m_availablePresentModes;
};
}

#endif // VT_SWAP_CHAIN_MANAGER_INCLUDE_H
