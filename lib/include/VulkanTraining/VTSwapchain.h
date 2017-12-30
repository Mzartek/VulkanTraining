#ifndef VT_SWAPCHAIN_INCLUDE_H
#define VT_SWAPCHAIN_INCLUDE_H

#include "VTDevice.h"

namespace VT
{
class LIB_INTERFACE Swapchain
{
public:
    Swapchain(const Device& device);
    virtual ~Swapchain();
    Swapchain(const Swapchain& other) = delete;
    Swapchain(Swapchain&& other) = delete;
    Swapchain& operator=(const Swapchain& other) = delete;
    Swapchain& operator=(Swapchain&& other) = delete;

    VkSwapchainKHR GetSwapchain();
    VkSwapchainKHR GetSwapchain() const;

    const std::vector<VkImage>& GetImages() const;

private:
    const Device& m_device;
    VkSwapchainKHR m_swapchain;

    std::vector<VkImage> m_images;
};
}

#endif