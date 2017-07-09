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

    std::vector<VkExtensionProperties> m_availableExtensions;
    std::vector<VkLayerProperties> m_availableLayers;

    void InitAvailableExtensions();
    void InitAvailableLayers();
    bool CheckExtensionSupport(const char* extensionName);
    bool CheckLayerSupport(const char* layerName);
    std::vector<const char*> GetExtensionNames(bool enableValidationLayers);
    std::vector<const char*> GetLayerNames(bool enableValidationLayers);
};
}

#endif
