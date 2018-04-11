#include <private/ShadersCollector.h>

#include <private/Device.h>

namespace fs = boost::filesystem;

namespace VT
{
ShadersCollector::ShadersCollector(Device& device, const std::string& shadersPath)
    : m_device(device)
    , m_vertexStaticObject(m_device, (fs::path(shadersPath) / "StaticObject/StaticObject.vert").string())
    , m_fragmentStaticObject(m_device, (fs::path(shadersPath) / "StaticObject/StaticObject.frag").string())
{
}

Device& ShadersCollector::GetRelatedDevice() const
{
    return m_device;
}

const Shader& ShadersCollector::GetVertexStaticObject() const
{
    return m_vertexStaticObject;
}

const Shader& ShadersCollector::GetFragmentStaticObject() const
{
    return m_fragmentStaticObject;
}
}
