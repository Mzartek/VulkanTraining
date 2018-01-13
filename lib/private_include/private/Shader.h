#ifndef VT_SHADER_INCLUDE_H
#define VT_SHADER_INCLUDE_H

#include "Device.h"

namespace VT
{
class Shader
{
public:
    Shader(const Device& device, const std::string& path);
    virtual ~Shader();
    Shader(const Shader& other) = delete;
    Shader(Shader&& other) = delete;
    Shader& operator=(const Shader& other) = delete;
    Shader& operator=(Shader&& other) = delete;

    const Device& GetRelatedDevice() const;

    VkShaderModule GetShaderModule() const;

private:
    const Device& m_device;

    VkShaderModule m_shaderModule;
};
}

#endif
