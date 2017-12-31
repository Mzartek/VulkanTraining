#ifndef VT_INSTANCE_EXTENSIONS_MANAGER_INCLUDE_H
#define VT_INSTANCE_EXTENSIONS_MANAGER_INCLUDE_H

#include "ExtensionsManager.h"

namespace VT
{
class LIB_INTERFACE InstanceExtensionsManager final : public ExtensionsManager
{
public:
    InstanceExtensionsManager();
    virtual ~InstanceExtensionsManager() = default;

    std::vector<const char*> GetMinimalExtensionNames(bool enableValidationLayers) override;
};
}

#endif
