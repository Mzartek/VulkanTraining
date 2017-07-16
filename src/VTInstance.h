#ifndef VT_INSTANCE_INCLUDE_H
#define VT_INSTANCE_INCLUDE_H

#include "VTWindow.h"

#include <vector>

namespace VT
{
class VTInstance
{
public:
    VTInstance(const std::string& applicationName, bool enableValidationLayers);
    virtual ~VTInstance();
    VTInstance(const VTInstance& other) = delete;
    VTInstance(VTInstance&& other) = delete;
    VTInstance& operator=(const VTInstance& other) = delete;
    VTInstance& operator=(VTInstance&& other) = delete;

    VkInstance GetInstance();
    VkInstance GetInstance() const;

private:
    VkInstance m_instance;
    VkDebugReportCallbackEXT m_callback;
    VkSurfaceKHR m_surface;
};
}

#endif
