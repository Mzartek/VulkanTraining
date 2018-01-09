#ifndef VT_SWAPCHAIN_INCLUDE_H
#define VT_SWAPCHAIN_INCLUDE_H

#include "Device.h"

namespace VT
{
class Swapchain
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

    const Device& GetRelatedDevice() const;

    const VkExtent2D& GetExtent() const;
    VkFormat GetFormat() const;
    const std::vector<VkImageView>& GetImageViews() const;

private:
    const Device& m_device;
    VkSwapchainKHR m_swapchain;

    VkExtent2D m_extent;
    VkFormat m_format;
    std::vector<VkImageView> m_imageViews;
};
}

#endif
