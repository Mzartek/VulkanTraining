#ifndef VT_EXTENSIONS_MANAGER_INCLUDE_H
#define VT_EXTENSIONS_MANAGER_INCLUDE_H

#include <vulkan/vulkan.h>

#include <vector>

namespace VT
{
class VTExtensionsManager
{
public:
    VTExtensionsManager() = default;
    virtual ~VTExtensionsManager() = default;
    VTExtensionsManager(const VTExtensionsManager& other) = delete;
    VTExtensionsManager(VTExtensionsManager&& other) = delete;
    VTExtensionsManager& operator=(const VTExtensionsManager& other) = delete;
    VTExtensionsManager& operator=(VTExtensionsManager&& other) = delete;

    bool CheckExtensionSupport(const char* extensionName);

    virtual std::vector<const char*> GetMinimalExtensionNames(bool enableValidationLayers) = 0;

protected:
    void SetAvailableExtensions(const std::vector<VkExtensionProperties>& availableExtensions);

private:
    std::vector<VkExtensionProperties> m_availableExtensions;
};
}

#endif
