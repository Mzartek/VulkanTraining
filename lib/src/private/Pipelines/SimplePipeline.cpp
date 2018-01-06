#include <private/Pipelines/SimplePipeline.h>

#include <boost/filesystem.hpp>

namespace
{
    std::string GetVertexShaderPath()
    {
        const boost::filesystem::path path = boost::filesystem::current_path() / "../shaders/src/Simple/vert.spv";
        return path.string();
    }

    std::string GetFragmentShaderPath()
    {
        const boost::filesystem::path path = boost::filesystem::current_path() / "../shaders/src/Simple/frag.spv";
        return path.string();
    }
}

namespace VT
{
SimplePipeline::SimplePipeline(const Swapchain& swapchain)
    : m_swapchain(swapchain)
    , m_vertexShader(m_swapchain.GetRelatedDevice(), GetVertexShaderPath())
    , m_fragmentShader(m_swapchain.GetRelatedDevice(), GetFragmentShaderPath())
{
}

SimplePipeline::~SimplePipeline()
{
}
}
