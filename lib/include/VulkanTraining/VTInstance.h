#ifndef VT_INSTANCE_INCLUDE_H
#define VT_INSTANCE_INCLUDE_H

#include "VTExport.h"

#include <vulkan/vulkan.h>

#include <string>

namespace VT
{
class LIB_INTERFACE Instance
{
public:
    Instance(const std::string& applicationName, bool enableValidationLayers);
    virtual ~Instance();
    Instance(const Instance& other) = delete;
    Instance(Instance&& other) = delete;
    Instance& operator=(const Instance& other) = delete;
    Instance& operator=(Instance&& other) = delete;

    VkInstance GetInstance();
    VkInstance GetInstance() const;

private:
    VkInstance m_instance;
    VkDebugReportCallbackEXT m_callback;
    VkSurfaceKHR m_surface;
};
}

#endif
