#ifndef VT_SHADER_INCLUDE_H
#define VT_SHADER_INCLUDE_H

#include "Device.h"

namespace VT
{
class Shader : public NonCopyableObject
{
public:
    Shader(Device& device, const std::string& filename);
    ~Shader() override;

    Device& GetRelatedDevice() const;

    VkShaderModule GetShaderModule() const;

private:
    Device& m_device;

    VkShaderModule m_shaderModule;
};
}

#endif
