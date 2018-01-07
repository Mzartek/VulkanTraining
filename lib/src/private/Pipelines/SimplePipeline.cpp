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
    /*VkPipelineShaderStageCreateInfo vertShaderStageInfo = {};
    vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
    vertShaderStageInfo.module = m_vertexShader.GetShaderModule();
    vertShaderStageInfo.pName = "main";

    VkPipelineShaderStageCreateInfo fragShaderStageInfo = {};
    fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    fragShaderStageInfo.module = m_fragmentShader.GetShaderModule();
    fragShaderStageInfo.pName = "main";

    VkPipelineShaderStageCreateInfo shaderStages[] = {vertShaderStageInfo, fragShaderStageInfo};

    VkPipelineVertexInputStateCreateInfo vertexInputInfo = {};
    vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertexInputInfo.vertexBindingDescriptionCount = 0;
    vertexInputInfo.pVertexBindingDescriptions = nullptr;
    vertexInputInfo.vertexAttributeDescriptionCount = 0;
    vertexInputInfo.pVertexAttributeDescriptions = nullptr;

    VkPipelineInputAssemblyStateCreateInfo inputAssembly = {};
    inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    inputAssembly.primitiveRestartEnable = VK_FALSE;

    VkViewport viewport = {};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = static_cast<float>(m_swapchain.GetExtent().width);
    viewport.height = static_cast<float>(m_swapchain.GetExtent().height);
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;*/
}

SimplePipeline::~SimplePipeline()
{
}
}
