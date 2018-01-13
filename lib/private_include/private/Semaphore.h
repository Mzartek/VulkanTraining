#ifndef VT_SEMAPHORE_INCLUDE_H
#define VT_SEMAPHORE_INCLUDE_H

#include "Device.h"

namespace VT
{
class Semaphore
{
public:
    Semaphore(const Device& device);
    virtual ~Semaphore();
    Semaphore(const Semaphore& other) = delete;
    Semaphore(Semaphore&& other) = delete;
    Semaphore& operator=(const Semaphore& other) = delete;
    Semaphore& operator=(Semaphore&& other) = delete;

    const Device& GetRelatedDevice() const;

    VkSemaphore GetSemaphore() const;

private:
    const Device& m_device;

    VkSemaphore m_semaphore;
};
}

#endif
