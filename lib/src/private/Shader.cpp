#include <private/Shader.h>

#include <fstream>

#include <boost/filesystem.hpp>

#include <SPIRV/GlslangToSpv.h>

namespace
{
    std::vector<char> ReadFile(const std::string& filename)
    {
        std::ifstream file(filename, std::ios::ate);

        if (!file.is_open())
        {
            const std::string message = "File not found (" + filename + ")";
            throw std::runtime_error(message);
        }

        const size_t fileSize = static_cast<size_t>(file.tellg());
        std::vector<char> buffer(fileSize);

        file.seekg(0);
        file.read(buffer.data(), fileSize);

        file.close();

        return buffer;
    }

    EShLanguage GetShaderType(const std::string& filename)
    {
        std::string filenameExtension = boost::filesystem::extension(filename);

        if (filenameExtension == ".vert")
            return EShLangVertex;
        if (filenameExtension == ".tesc")
            return EShLangTessControl;
        if (filenameExtension == ".tese")
            return EShLangTessEvaluation;
        if (filenameExtension == ".geom")
            return EShLangGeometry;
        if (filenameExtension == ".frag")
            return EShLangFragment;
        if (filenameExtension != ".comp")
            throw std::runtime_error("Can't find shader type");

        return EShLangCompute;
    }

    std::vector<unsigned int> GLSLtoSPV(const std::string& filename)
    {
        std::vector<char> textBuffer = ReadFile(filename);
        std::vector<unsigned int> spirv;

        glslang::InitializeProcess();

        glslang::TProgram program;
        TBuiltInResource Resources = {};
        const char* shaderStrings[] = { textBuffer.data() };

        EShLanguage stage = GetShaderType(filename);
        glslang::TShader shader(stage);
        shader.setStrings(shaderStrings, 1);

        EShMessages msgs = static_cast<EShMessages>(EShMsgSpvRules | EShMsgVulkanRules);
        if (!shader.parse(&Resources, 100, false, msgs))
        {
            puts(shader.getInfoLog());
            puts(shader.getInfoDebugLog());
            throw std::runtime_error("Failed to build shader " + filename);
        }

        glslang::GlslangToSpv(*program.getIntermediate(stage), spirv);

        glslang::FinalizeProcess();

        return spirv;
    }
}

namespace VT
{
Shader::Shader(Device& device, const std::string& filename)
    : m_device(device)
    , m_shaderModule(VK_NULL_HANDLE)
{
    std::vector<unsigned int> spirv = GLSLtoSPV(filename);

    VkShaderModuleCreateInfo shaderModuleCreateInfo = {};
    shaderModuleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    shaderModuleCreateInfo.codeSize = spirv.size() * sizeof(unsigned int);
    shaderModuleCreateInfo.pCode = spirv.data();

    VkResult result = vkCreateShaderModule(m_device.GetDevice(), &shaderModuleCreateInfo, nullptr, &m_shaderModule);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Failed to create shader module");
}

Shader::~Shader()
{
    vkDestroyShaderModule(m_device.GetDevice(), m_shaderModule, nullptr);
}

Device& Shader::GetRelatedDevice() const
{
    return m_device;
}

VkShaderModule Shader::GetShaderModule() const
{
    return m_shaderModule;
}
}
