#ifndef VT_INSTANCE_INCLUDE_H
#define VT_INSTANCE_INCLUDE_H

#include "NonCopyableObject.h"

namespace VT
{
class Instance : public NonCopyableObject
{
public:
    Instance(const std::string& applicationName, bool enableValidationLayers);
    ~Instance() override;

    VkInstance GetInstance() const;

private:
    VkInstance m_instance;
    VkDebugReportCallbackEXT m_callback;
    VkSurfaceKHR m_surface;
};
}

#endif
