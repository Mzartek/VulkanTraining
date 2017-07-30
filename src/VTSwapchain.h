#ifndef VT_SWAPCHAIN_INCLUDE_H
#define VT_SWAPCHAIN_INCLUDE_H

#include "VTDevice.h"

namespace VT
{
class VTSwapchain
{
public:
    VTSwapchain(const VTDevice& vtDevice);
    virtual ~VTSwapchain();
    VTSwapchain(const VTSwapchain& other) = delete;
    VTSwapchain(VTSwapchain&& other) = delete;
    VTSwapchain& operator=(const VTSwapchain& other) = delete;
    VTSwapchain& operator=(VTSwapchain&& other) = delete;

    VkSwapchainKHR GetSwapchain();
    VkSwapchainKHR GetSwapchain() const;

    const std::vector<VkImage>& GetImages() const;

private:
    const VTDevice& m_device;
    VkSwapchainKHR m_swapchain;

    std::vector<VkImage> m_images;
};
}

#endif
