#include <private/Shader.h>

#include <fstream>

namespace
{
    std::vector<char> ReadFile(const std::string& path)
    {
        std::ifstream file(path, std::ios::ate | std::ios::binary);

        if (!file.is_open())
            throw std::runtime_error("File is not opened");

        const size_t fileSize = static_cast<size_t>(file.tellg());
        std::vector<char> buffer(fileSize);

        file.seekg(0);
        file.read(buffer.data(), fileSize);

        file.close();

        return buffer;
    }
}

namespace VT
{
Shader::Shader(const Device& device, const std::string& path)
    : m_device(device)
    , m_shaderModule(VK_NULL_HANDLE)
{
    std::vector<char> buffer = ReadFile(path);

    VkShaderModuleCreateInfo shaderModuleCreateInfo = {};
    shaderModuleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    shaderModuleCreateInfo.codeSize = buffer.size();
    shaderModuleCreateInfo.pCode = reinterpret_cast<uint32_t*>(buffer.data());

    VkResult result = vkCreateShaderModule(m_device.GetDevice(), &shaderModuleCreateInfo, nullptr, &m_shaderModule);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Failed to create shader module");
}

Shader::~Shader()
{
    vkDestroyShaderModule(m_device.GetDevice(), m_shaderModule, nullptr);
}

VkShaderModule Shader::GetShaderModule()
{
    return m_shaderModule;
}

VkShaderModule Shader::GetShaderModule() const
{
    return m_shaderModule;
}
}
