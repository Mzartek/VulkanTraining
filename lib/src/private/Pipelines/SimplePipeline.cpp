#include <private/Pipelines/SimplePipeline.h>

#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

namespace
{
    std::string GetVertexShaderPath(const std::string& shadersPath)
    {
        const fs::path fullPath = fs::path(shadersPath) / "Simple/vert.spv";
        return fullPath.string();
    }

    std::string GetFragmentShaderPath(const std::string& shadersPath)
    {
        const fs::path fullPath = fs::path(shadersPath) / "Simple/frag.spv";
        return fullPath.string();
    }
}

namespace VT
{
SimplePipeline::SimplePipeline(const Swapchain& swapchain, const std::string& shadersPath)
    : m_swapchain(swapchain)
    , m_vertexShader(m_swapchain.GetRelatedDevice(), GetVertexShaderPath(shadersPath))
    , m_fragmentShader(m_swapchain.GetRelatedDevice(), GetFragmentShaderPath(shadersPath))
{
}

SimplePipeline::~SimplePipeline()
{
}
}
