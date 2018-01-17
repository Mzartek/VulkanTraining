#ifndef VT_SWAPCHAIN_INCLUDE_H
#define VT_SWAPCHAIN_INCLUDE_H

#include "Device.h"

namespace VT
{
class SwapchainOutOfDateException : public std::exception
{};

class Swapchain
{
public:
    Swapchain(Device& device);
    virtual ~Swapchain();
    Swapchain(const Swapchain& other) = delete;
    Swapchain(Swapchain&& other) = delete;
    Swapchain& operator=(const Swapchain& other) = delete;
    Swapchain& operator=(Swapchain&& other) = delete;

    Device& GetRelatedDevice() const;

    const VkExtent2D& GetExtent2D() const;
    VkFormat GetFormat() const;

    VkSwapchainKHR GetSwapchain() const;

    const std::vector<VkImageView>& GetImageViews() const;
    const std::vector<VkSemaphore>& GetSemaphores() const;

    void LoadNextImage();
    void RegisterSemaphoreToWait(VkSemaphore semaphoreToWait);
    void PresentImage();

    uint32_t GetCurrentImageViewIndex() const;
    uint32_t GetCurrentSemaphoreIndex() const;

private:
    Device& m_device;

    VkExtent2D m_extend2D;
    VkFormat m_format;

    VkSwapchainKHR m_swapchain;

    std::vector<VkImageView> m_imageViews;
    std::vector<VkSemaphore> m_semaphores;

    uint32_t m_currentImageViewIndex;
    uint32_t m_currentSemaphoreIndex;

    uint32_t m_nextSemaphoreIndex;

    std::vector<VkSemaphore> m_registeredSemaphoresToWait;
};
}

#endif
