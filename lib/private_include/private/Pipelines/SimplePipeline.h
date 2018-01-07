#ifndef VT_SIMPLE_PIPELINE_INCLUDE_H
#define VT_SIMPLE_PIPELINE_INCLUDE_H

#include "../Swapchain.h"
#include "../Shader.h"

namespace VT
{
class SimplePipeline
{
public:
    SimplePipeline(const Swapchain& swapchain, const std::string& shadersPath);
    virtual ~SimplePipeline();
    SimplePipeline(const SimplePipeline& other) = delete;
    SimplePipeline(SimplePipeline&& other) = delete;
    SimplePipeline& operator=(const SimplePipeline& other) = delete;
    SimplePipeline& operator=(SimplePipeline&& other) = delete;

private:
    const Swapchain& m_swapchain;

    Shader m_vertexShader;
    Shader m_fragmentShader;
};
}

#endif
