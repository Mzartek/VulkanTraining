#ifndef VT_EXTENSIONS_MANAGER_INCLUDE_H
#define VT_EXTENSIONS_MANAGER_INCLUDE_H

#include "VTExport.h"

#include <vulkan/vulkan.h>

#include <vector>

namespace VT
{
class LIB_INTERFACE ExtensionsManager
{
public:
    ExtensionsManager() = default;
    virtual ~ExtensionsManager() = default;

    bool CheckExtensionSupport(const char* extensionName);

    virtual std::vector<const char*> GetMinimalExtensionNames(bool enableValidationLayers) = 0;

protected:
    void SetAvailableExtensions(const std::vector<VkExtensionProperties>& availableExtensions);

private:
    std::vector<VkExtensionProperties> m_availableExtensions;
};
}

#endif
