#include <VulkanTraining/VTExtensionsManager.h>

#include <cstring>

namespace VT
{
bool ExtensionsManager::CheckExtensionSupport(const char* extensionName)
{
    for (const auto& extension : m_availableExtensions)
        if (strcmp(extensionName, extension.extensionName) == 0)
            return true;

    return false;
}

void ExtensionsManager::SetAvailableExtensions(const std::vector<VkExtensionProperties>& availableExtensions)
{
    m_availableExtensions = availableExtensions;
}
}
