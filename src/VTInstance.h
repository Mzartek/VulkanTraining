#ifndef VT_INSTANCE_INCLUDE_H
#define VT_INSTANCE_INCLUDE_H

#include "VTWindow.h"

#include <vector>

namespace VT
{
class VTInstance
{
public:
    VTInstance(const VTWindow& vtWindow, bool enableValidationLayers);
    virtual ~VTInstance();
    VTInstance(const VTInstance& other) = delete;
    VTInstance(VTInstance&& other) = delete;
    VTInstance& operator=(const VTInstance& other) = delete;
    VTInstance& operator=(VTInstance&& other) = delete;

    VkInstance GetInstance();
    const VkInstance GetInstance() const;

private:
    VkInstance m_instance;
    VkDebugReportCallbackEXT m_callback;
};
}

#endif
