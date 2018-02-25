#ifndef VT_SHADERS_COLLECTOR_INCLUDE_H
#define VT_SHADERS_COLLECTOR_INCLUDE_H

#include "Shader.h"

namespace VT
{
class ShadersCollector : public NonCopyableObject
{
public:
    ShadersCollector(Device& device, const std::string& shadersPath);

    Device& GetRelatedDevice() const;

    const Shader& GetVertexStaticObject() const;
    const Shader& GetFragmentStaticObject() const;

private:
    Device& m_device;

    Shader m_vertexStaticObject;
    Shader m_fragmentStaticObject;
};
}

#endif
