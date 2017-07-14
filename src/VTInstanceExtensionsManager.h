#ifndef VT_INSTANCE_EXTENSIONS_MANAGER_INCLUDE_H
#define VT_INSTANCE_EXTENSIONS_MANAGER_INCLUDE_H

#include "VTExtensionsManager.h"

namespace VT
{
class VTInstanceExtensionsManager final : public VTExtensionsManager
{
public:
    VTInstanceExtensionsManager();

    std::vector<const char*> GetMinimalExtensionNames(bool enableValidationLayers) override;
};
}

#endif
