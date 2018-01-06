#include <private/Pipelines/SimplePipeline.h>

namespace VT
{
SimplePipeline::SimplePipeline(const Swapchain& swapchain)
    : m_swapchain(swapchain)
    , m_vertexShader(m_swapchain.GetRelatedDevice(), "")
    , m_fragmentShader(m_swapchain.GetRelatedDevice(), "")
{
}

SimplePipeline::~SimplePipeline()
{
}
}
