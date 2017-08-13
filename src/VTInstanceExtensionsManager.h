#ifndef VT_INSTANCE_EXTENSIONS_MANAGER_INCLUDE_H
#define VT_INSTANCE_EXTENSIONS_MANAGER_INCLUDE_H

#include "VTExtensionsManager.h"

namespace VT
{
class InstanceExtensionsManager final : public ExtensionsManager
{
public:
    InstanceExtensionsManager();
    virtual ~InstanceExtensionsManager() = default;
    InstanceExtensionsManager(const InstanceExtensionsManager& other) = delete;
    InstanceExtensionsManager(InstanceExtensionsManager&& other) = delete;
    InstanceExtensionsManager& operator=(const InstanceExtensionsManager& other) = delete;
    InstanceExtensionsManager& operator=(InstanceExtensionsManager&& other) = delete;

    std::vector<const char*> GetMinimalExtensionNames(bool enableValidationLayers) override;
};
}

#endif
