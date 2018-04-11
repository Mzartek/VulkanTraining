#include <private/Shader.h>

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

        buffer.push_back('\0');

        return buffer;
    }

    TBuiltInResource GetRessources()
    {
        TBuiltInResource ressources = {};
        ressources.maxLights = 32;
        ressources.maxClipPlanes = 6;
        ressources.maxTextureUnits = 32;
        ressources.maxTextureCoords = 32;
        ressources.maxVertexAttribs = 64;
        ressources.maxVertexUniformComponents = 4096;
        ressources.maxVaryingFloats = 64;
        ressources.maxVertexTextureImageUnits = 32;
        ressources.maxCombinedTextureImageUnits = 80;
        ressources.maxTextureImageUnits = 32;
        ressources.maxFragmentUniformComponents = 4096;
        ressources.maxDrawBuffers = 32;
        ressources.maxVertexUniformVectors = 128;
        ressources.maxVaryingVectors = 8;
        ressources.maxFragmentUniformVectors = 16;
        ressources.maxVertexOutputVectors = 16;
        ressources.maxFragmentInputVectors = 15;
        ressources.minProgramTexelOffset = -8;
        ressources.maxProgramTexelOffset = 7;
        ressources.maxClipDistances = 8;
        ressources.maxComputeWorkGroupCountX = 65535;
        ressources.maxComputeWorkGroupCountY = 65535;
        ressources.maxComputeWorkGroupCountZ = 65535;
        ressources.maxComputeWorkGroupSizeX = 1024;
        ressources.maxComputeWorkGroupSizeY = 1024;
        ressources.maxComputeWorkGroupSizeZ = 64;
        ressources.maxComputeUniformComponents = 1024;
        ressources.maxComputeTextureImageUnits = 16;
        ressources.maxComputeImageUniforms = 8;
        ressources.maxComputeAtomicCounters = 8;
        ressources.maxComputeAtomicCounterBuffers = 1;
        ressources.maxVaryingComponents = 60;
        ressources.maxVertexOutputComponents = 64;
        ressources.maxGeometryInputComponents = 64;
        ressources.maxGeometryOutputComponents = 128;
        ressources.maxFragmentInputComponents = 128;
        ressources.maxImageUnits = 8;
        ressources.maxCombinedImageUnitsAndFragmentOutputs = 8;
        ressources.maxCombinedShaderOutputResources = 8;
        ressources.maxImageSamples = 0;
        ressources.maxVertexImageUniforms = 0;
        ressources.maxTessControlImageUniforms = 0;
        ressources.maxTessEvaluationImageUniforms = 0;
        ressources.maxGeometryImageUniforms = 0;
        ressources.maxFragmentImageUniforms = 8;
        ressources.maxCombinedImageUniforms = 8;
        ressources.maxGeometryTextureImageUnits = 16;
        ressources.maxGeometryOutputVertices = 256;
        ressources.maxGeometryTotalOutputComponents = 1024;
        ressources.maxGeometryUniformComponents = 1024;
        ressources.maxGeometryVaryingComponents = 64;
        ressources.maxTessControlInputComponents = 128;
        ressources.maxTessControlOutputComponents = 128;
        ressources.maxTessControlTextureImageUnits = 16;
        ressources.maxTessControlUniformComponents = 1024;
        ressources.maxTessControlTotalOutputComponents = 4096;
        ressources.maxTessEvaluationInputComponents = 128;
        ressources.maxTessEvaluationOutputComponents = 128;
        ressources.maxTessEvaluationTextureImageUnits = 16;
        ressources.maxTessEvaluationUniformComponents = 1024;
        ressources.maxTessPatchComponents = 120;
        ressources.maxPatchVertices = 32;
        ressources.maxTessGenLevel = 64;
        ressources.maxViewports = 16;
        ressources.maxVertexAtomicCounters = 0;
        ressources.maxTessControlAtomicCounters = 0;
        ressources.maxTessEvaluationAtomicCounters = 0;
        ressources.maxGeometryAtomicCounters = 0;
        ressources.maxFragmentAtomicCounters = 8;
        ressources.maxCombinedAtomicCounters = 8;
        ressources.maxAtomicCounterBindings = 1;
        ressources.maxVertexAtomicCounterBuffers = 0;
        ressources.maxTessControlAtomicCounterBuffers = 0;
        ressources.maxTessEvaluationAtomicCounterBuffers = 0;
        ressources.maxGeometryAtomicCounterBuffers = 0;
        ressources.maxFragmentAtomicCounterBuffers = 1;
        ressources.maxCombinedAtomicCounterBuffers = 1;
        ressources.maxAtomicCounterBufferSize = 16384;
        ressources.maxTransformFeedbackBuffers = 4;
        ressources.maxTransformFeedbackInterleavedComponents = 64;
        ressources.maxCullDistances = 8;
        ressources.maxCombinedClipAndCullDistances = 8;
        ressources.maxSamples = 4;
        ressources.limits.nonInductiveForLoops = 1;
        ressources.limits.whileLoops = 1;
        ressources.limits.doWhileLoops = 1;
        ressources.limits.generalUniformIndexing = 1;
        ressources.limits.generalAttributeMatrixVectorIndexing = 1;
        ressources.limits.generalVaryingIndexing = 1;
        ressources.limits.generalSamplerIndexing = 1;
        ressources.limits.generalVariableIndexing = 1;
        ressources.limits.generalConstantMatrixVectorIndexing = 1;

        return ressources;
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
        TBuiltInResource resources = GetRessources();
        EShLanguage stage = GetShaderType(filename);
        const char* shaderStrings[] = { textBuffer.data() };

        EShMessages msgs = static_cast<EShMessages>(EShMsgSpvRules | EShMsgVulkanRules);

        glslang::TShader shader(stage);
        shader.setStrings(shaderStrings, 1);

        if (!shader.parse(&resources, 100, false, msgs))
        {
            puts(shader.getInfoLog());
            puts(shader.getInfoDebugLog());
            throw std::runtime_error("Failed to build shader " + filename);
        }

        program.addShader(&shader);

        if (!program.link(msgs))
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
