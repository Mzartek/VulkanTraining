#ifndef VT_SWAP_CHAIN_MANAGER_INCLUDE_H
#define VT_SWAP_CHAIN_MANAGER_INCLUDE_H

#include "VTPhysicalDevice.h"
#include "VTSurface.h"

namespace VT
{
class VTSwapChainManager
{
public:
    VTSwapChainManager(const VTPhysicalDevice& vtPhysicalDevice, const VTSurface& vtSurface);
    virtual ~VTSwapChainManager() = default;
    VTSwapChainManager(const VTSwapChainManager& other) = delete;
    VTSwapChainManager(VTSwapChainManager&& other) = delete;
    VTSwapChainManager& operator=(const VTSwapChainManager& other) = delete;
    VTSwapChainManager& operator=(VTSwapChainManager&& other) = delete;

    VkSurfaceFormatKHR GetSurfaceFormat() const;
    VkPresentModeKHR GetPresentMode() const;
    VkExtent2D GetExtent2D() const;

private:
    const VTSurface& m_surface;

    VkSurfaceCapabilitiesKHR m_surfaceCapabilities;
    std::vector<VkSurfaceFormatKHR> m_availableSurfaceFormats;
    std::vector<VkPresentModeKHR> m_availablePresentModes;
};
}

#endif // VT_SWAP_CHAIN_MANAGER_INCLUDE_H
