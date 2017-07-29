#ifndef VT_INSTANCE_EXTENSIONS_MANAGER_INCLUDE_H
#define VT_INSTANCE_EXTENSIONS_MANAGER_INCLUDE_H

#include "VTExtensionsManager.h"

namespace VT
{
class VTInstanceExtensionsManager final : public VTExtensionsManager
{
public:
    VTInstanceExtensionsManager();
    virtual ~VTInstanceExtensionsManager() = default;
    VTInstanceExtensionsManager(const VTInstanceExtensionsManager& other) = delete;
    VTInstanceExtensionsManager(VTInstanceExtensionsManager&& other) = delete;
    VTInstanceExtensionsManager& operator=(const VTInstanceExtensionsManager& other) = delete;
    VTInstanceExtensionsManager& operator=(VTInstanceExtensionsManager&& other) = delete;

    std::vector<const char*> GetMinimalExtensionNames(bool enableValidationLayers) override;
};
}

#endif
