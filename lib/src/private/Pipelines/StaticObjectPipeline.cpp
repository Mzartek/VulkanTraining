#include <private/Pipelines/StaticObjectPipeline.h>

namespace
{
VkResult CreateDescriptorSetLayout(VkDevice device, VkDescriptorSetLayout& descriptorSetLayout)
{
    VkDescriptorSetLayoutBinding descriptorSetLayoutBinding = {};
    descriptorSetLayoutBinding.binding = 0;
    descriptorSetLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    descriptorSetLayoutBinding.descriptorCount = 1;
    descriptorSetLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
    descriptorSetLayoutBinding.pImmutableSamplers = nullptr;

    VkDescriptorSetLayoutCreateInfo descriptorSetLayoutCreateInfo = {};
    descriptorSetLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    descriptorSetLayoutCreateInfo.bindingCount = 1;
    descriptorSetLayoutCreateInfo.pBindings = &descriptorSetLayoutBinding;

    return vkCreateDescriptorSetLayout(device, &descriptorSetLayoutCreateInfo, nullptr, &descriptorSetLayout);
}

VkResult CreateDescriptorPool(VkDevice device, VkDescriptorPool& descriptorPool)
{
    VkDescriptorPoolSize descriptorPoolSize = {};
    descriptorPoolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    descriptorPoolSize.descriptorCount = 1;

    VkDescriptorPoolCreateInfo descriptorPoolCreateInfo = {};
    descriptorPoolCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    descriptorPoolCreateInfo.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
    descriptorPoolCreateInfo.poolSizeCount = 1;
    descriptorPoolCreateInfo.pPoolSizes = &descriptorPoolSize;
    descriptorPoolCreateInfo.maxSets = 1;

    return vkCreateDescriptorPool(device, &descriptorPoolCreateInfo, nullptr, &descriptorPool);
}

VkResult AllocateDescriptorSet(VkDevice device, VkDescriptorSetLayout descriptorSetLayout, VkDescriptorPool descriptorPool, VkDescriptorSet& descriptorSet)
{
    VkDescriptorSetLayout descriptorSetLayouts[] = { descriptorSetLayout };

    VkDescriptorSetAllocateInfo descriptorSetAllocateInfo = {};
    descriptorSetAllocateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    descriptorSetAllocateInfo.descriptorPool = descriptorPool;
    descriptorSetAllocateInfo.descriptorSetCount = 1;
    descriptorSetAllocateInfo.pSetLayouts = descriptorSetLayouts;

    return vkAllocateDescriptorSets(device, &descriptorSetAllocateInfo, &descriptorSet);
}

VkResult CreatePipelineLayout(VkDevice device, VkDescriptorSetLayout descriptorSetLayout, VkPipelineLayout& pipelineLayout)
{
    VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo = {};
    pipelineLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutCreateInfo.setLayoutCount = 1;
    pipelineLayoutCreateInfo.pSetLayouts = &descriptorSetLayout;
    pipelineLayoutCreateInfo.pushConstantRangeCount = 0;
    pipelineLayoutCreateInfo.pPushConstantRanges = 0;

    return vkCreatePipelineLayout(device, &pipelineLayoutCreateInfo, nullptr, &pipelineLayout);
}

VkResult CreateRenderPass(VkDevice device, VkFormat format, VkRenderPass& renderPass)
{
    VkAttachmentDescription attachmentDescription = {};
    attachmentDescription.format = format;
    attachmentDescription.samples = VK_SAMPLE_COUNT_1_BIT;
    attachmentDescription.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    attachmentDescription.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    attachmentDescription.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    attachmentDescription.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    attachmentDescription.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    attachmentDescription.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

    VkAttachmentReference attachmentReference = {};
    attachmentReference.attachment = 0;
    attachmentReference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkSubpassDescription subpassDescription = {};
    subpassDescription.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpassDescription.colorAttachmentCount = 1;
    subpassDescription.pColorAttachments = &attachmentReference;

    VkSubpassDependency subpassDependency = {};
    subpassDependency.srcSubpass = VK_SUBPASS_EXTERNAL;
    subpassDependency.dstSubpass = 0;
    subpassDependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    subpassDependency.srcAccessMask = 0;
    subpassDependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    subpassDependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

    VkRenderPassCreateInfo renderPassCreateInfo = {};
    renderPassCreateInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderPassCreateInfo.attachmentCount = 1;
    renderPassCreateInfo.pAttachments = &attachmentDescription;
    renderPassCreateInfo.subpassCount = 1;
    renderPassCreateInfo.pSubpasses = &subpassDescription;
    renderPassCreateInfo.dependencyCount = 1;
    renderPassCreateInfo.pDependencies = &subpassDependency;

    return vkCreateRenderPass(device, &renderPassCreateInfo, nullptr, &renderPass);
}

VkResult CreateGraphicPipeline(VkDevice device,
    VkShaderModule vertexShaderModule,
    VkShaderModule fragmentShaderModule,
    VkPipelineLayout pipelineLayout,
    VkRenderPass renderPass,
    VkExtent2D extent,
    VkPipeline& graphicsPipeline)
{
    VkPipelineShaderStageCreateInfo vertexPipelineShaderStageCreateInfo = {};
    vertexPipelineShaderStageCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    vertexPipelineShaderStageCreateInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
    vertexPipelineShaderStageCreateInfo.module = vertexShaderModule;
    vertexPipelineShaderStageCreateInfo.pName = "main";

    VkPipelineShaderStageCreateInfo fragmentPipelineShaderStageCreateInfo = {};
    fragmentPipelineShaderStageCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    fragmentPipelineShaderStageCreateInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    fragmentPipelineShaderStageCreateInfo.module = fragmentShaderModule;
    fragmentPipelineShaderStageCreateInfo.pName = "main";

    VkPipelineShaderStageCreateInfo pipelineShaderStageCreateInfos[] =
    {
        vertexPipelineShaderStageCreateInfo,
        fragmentPipelineShaderStageCreateInfo
    };

    VkVertexInputBindingDescription vertexInputBindingDescription = {};
    vertexInputBindingDescription.binding = 0;
    vertexInputBindingDescription.stride = sizeof(VT::StaticObjectPipeline::Vertex);
    vertexInputBindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

    std::array<VkVertexInputAttributeDescription, 2> vertexInputAttributeDescriptions = {};
    vertexInputAttributeDescriptions[0].binding = 0;
    vertexInputAttributeDescriptions[0].location = 0;
    vertexInputAttributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
    vertexInputAttributeDescriptions[0].offset = offsetof(VT::StaticObjectPipeline::Vertex, position);
    vertexInputAttributeDescriptions[1].binding = 0;
    vertexInputAttributeDescriptions[1].location = 1;
    vertexInputAttributeDescriptions[1].format = VK_FORMAT_R32G32_SFLOAT;
    vertexInputAttributeDescriptions[1].offset = offsetof(VT::StaticObjectPipeline::Vertex, texCoord);

    VkPipelineVertexInputStateCreateInfo pipelineVertexInputStateCreateInfo = {};
    pipelineVertexInputStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    pipelineVertexInputStateCreateInfo.vertexBindingDescriptionCount = 1;
    pipelineVertexInputStateCreateInfo.pVertexBindingDescriptions = &vertexInputBindingDescription;
    pipelineVertexInputStateCreateInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(vertexInputAttributeDescriptions.size());
    pipelineVertexInputStateCreateInfo.pVertexAttributeDescriptions = vertexInputAttributeDescriptions.data();

    VkPipelineInputAssemblyStateCreateInfo pipelineInputAssemblyStateCreateInfo = {};
    pipelineInputAssemblyStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    pipelineInputAssemblyStateCreateInfo.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    pipelineInputAssemblyStateCreateInfo.primitiveRestartEnable = VK_FALSE;

    VkViewport viewport = {};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = static_cast<float>(extent.width);
    viewport.height = static_cast<float>(extent.height);
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;

    VkRect2D scissor = {};
    scissor.offset = { 0, 0 };
    scissor.extent = extent;

    VkPipelineViewportStateCreateInfo pipelineViewportStateCreateInfo = {};
    pipelineViewportStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    pipelineViewportStateCreateInfo.viewportCount = 1;
    pipelineViewportStateCreateInfo.pViewports = &viewport;
    pipelineViewportStateCreateInfo.scissorCount = 1;
    pipelineViewportStateCreateInfo.pScissors = &scissor;

    VkPipelineRasterizationStateCreateInfo pipelineRasterizationStateCreateInfo = {};
    pipelineRasterizationStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    pipelineRasterizationStateCreateInfo.depthClampEnable = VK_FALSE;
    pipelineRasterizationStateCreateInfo.rasterizerDiscardEnable = VK_FALSE;
    pipelineRasterizationStateCreateInfo.polygonMode = VK_POLYGON_MODE_FILL;
    pipelineRasterizationStateCreateInfo.lineWidth = 1.0f;
    pipelineRasterizationStateCreateInfo.cullMode = VK_CULL_MODE_BACK_BIT;
    pipelineRasterizationStateCreateInfo.frontFace = VK_FRONT_FACE_CLOCKWISE;
    pipelineRasterizationStateCreateInfo.depthBiasEnable = VK_FALSE;
    pipelineRasterizationStateCreateInfo.depthBiasConstantFactor = 0.0f;
    pipelineRasterizationStateCreateInfo.depthBiasClamp = 0.0f;
    pipelineRasterizationStateCreateInfo.depthBiasSlopeFactor = 0.0f;

    VkPipelineMultisampleStateCreateInfo pipelineMultisampleStateCreateInfo = {};
    pipelineMultisampleStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    pipelineMultisampleStateCreateInfo.sampleShadingEnable = VK_FALSE;
    pipelineMultisampleStateCreateInfo.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
    pipelineMultisampleStateCreateInfo.minSampleShading = 1.0f;
    pipelineMultisampleStateCreateInfo.pSampleMask = nullptr;
    pipelineMultisampleStateCreateInfo.alphaToCoverageEnable = VK_FALSE;
    pipelineMultisampleStateCreateInfo.alphaToOneEnable = VK_FALSE;

    VkPipelineDepthStencilStateCreateInfo pipelineDepthStencilStateCreateInfo = {};
    pipelineDepthStencilStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;

    VkPipelineColorBlendAttachmentState pipelineColorBlendAttachmentState = {};
    pipelineColorBlendAttachmentState.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
    pipelineColorBlendAttachmentState.blendEnable = VK_FALSE;
    pipelineColorBlendAttachmentState.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
    pipelineColorBlendAttachmentState.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
    pipelineColorBlendAttachmentState.colorBlendOp = VK_BLEND_OP_ADD;
    pipelineColorBlendAttachmentState.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
    pipelineColorBlendAttachmentState.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
    pipelineColorBlendAttachmentState.alphaBlendOp = VK_BLEND_OP_ADD;

    VkPipelineColorBlendStateCreateInfo pipelineColorBlendStateCreateInfo = {};
    pipelineColorBlendStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    pipelineColorBlendStateCreateInfo.logicOpEnable = VK_FALSE;
    pipelineColorBlendStateCreateInfo.logicOp = VK_LOGIC_OP_COPY;
    pipelineColorBlendStateCreateInfo.attachmentCount = 1;
    pipelineColorBlendStateCreateInfo.pAttachments = &pipelineColorBlendAttachmentState;
    pipelineColorBlendStateCreateInfo.blendConstants[0] = 0.0f;
    pipelineColorBlendStateCreateInfo.blendConstants[1] = 0.0f;
    pipelineColorBlendStateCreateInfo.blendConstants[2] = 0.0f;
    pipelineColorBlendStateCreateInfo.blendConstants[3] = 0.0f;

    VkDynamicState dynamicStates[] =
    {
        VK_DYNAMIC_STATE_LINE_WIDTH
    };

    VkPipelineDynamicStateCreateInfo pipelineDynamicStateCreateInfo = {};
    pipelineDynamicStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    pipelineDynamicStateCreateInfo.dynamicStateCount = 1;
    pipelineDynamicStateCreateInfo.pDynamicStates = dynamicStates;

    VkGraphicsPipelineCreateInfo graphicsPipelineCreateInfo = {};
    graphicsPipelineCreateInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    graphicsPipelineCreateInfo.stageCount = 2;
    graphicsPipelineCreateInfo.pStages = pipelineShaderStageCreateInfos;
    graphicsPipelineCreateInfo.pVertexInputState = &pipelineVertexInputStateCreateInfo;
    graphicsPipelineCreateInfo.pInputAssemblyState = &pipelineInputAssemblyStateCreateInfo;
    graphicsPipelineCreateInfo.pViewportState = &pipelineViewportStateCreateInfo;
    graphicsPipelineCreateInfo.pRasterizationState = &pipelineRasterizationStateCreateInfo;
    graphicsPipelineCreateInfo.pMultisampleState = &pipelineMultisampleStateCreateInfo;
    graphicsPipelineCreateInfo.pDepthStencilState = &pipelineDepthStencilStateCreateInfo;
    graphicsPipelineCreateInfo.pColorBlendState = &pipelineColorBlendStateCreateInfo;
    graphicsPipelineCreateInfo.pDynamicState = &pipelineDynamicStateCreateInfo;
    graphicsPipelineCreateInfo.layout = pipelineLayout;
    graphicsPipelineCreateInfo.renderPass = renderPass;
    graphicsPipelineCreateInfo.subpass = 0;
    graphicsPipelineCreateInfo.basePipelineHandle = VK_NULL_HANDLE;
    graphicsPipelineCreateInfo.basePipelineIndex = -1;

    return vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &graphicsPipelineCreateInfo, nullptr, &graphicsPipeline);
}

VkResult CreateFramebuffer(VkDevice device, VkRenderPass renderPass, VkImageView imageView, VkExtent2D extent, VkFramebuffer& framebuffer)
{
    VkFramebufferCreateInfo framebufferCreateInfo = {};
    framebufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    framebufferCreateInfo.renderPass = renderPass;
    framebufferCreateInfo.attachmentCount = 1;
    framebufferCreateInfo.pAttachments = &imageView;
    framebufferCreateInfo.width = extent.width;
    framebufferCreateInfo.height = extent.height;
    framebufferCreateInfo.layers = 1;

    return vkCreateFramebuffer(device, &framebufferCreateInfo, nullptr, &framebuffer);
}
}

namespace VT
{
StaticObjectPipeline::StaticObjectPipeline(Swapchain& swapchain, const ShadersCollector& shadersCollector)
    : m_swapchain(swapchain)
    , m_descriptorSetLayout(VK_NULL_HANDLE)
    , m_descriptorPool(VK_NULL_HANDLE)
    , m_descriptorSet(VK_NULL_HANDLE)
    , m_pipelineLayout(VK_NULL_HANDLE)
    , m_renderPass(VK_NULL_HANDLE)
    , m_graphicsPipeline(VK_NULL_HANDLE)
    , m_transform(m_swapchain.GetRelatedDevice())
{
    VkResult result = CreateDescriptorSetLayout(m_swapchain.GetRelatedDevice().GetDevice(), m_descriptorSetLayout);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Failed to create descriptor set layout");

    result = CreateDescriptorPool(m_swapchain.GetRelatedDevice().GetDevice(), m_descriptorPool);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Failed to create descriptor pool");

    result = AllocateDescriptorSet(m_swapchain.GetRelatedDevice().GetDevice(), m_descriptorSetLayout, m_descriptorPool, m_descriptorSet);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Failed to allocate descriptor set");

    result = CreatePipelineLayout(m_swapchain.GetRelatedDevice().GetDevice(), m_descriptorSetLayout, m_pipelineLayout);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Failed to create pipeline layout");

    result = CreateRenderPass(m_swapchain.GetRelatedDevice().GetDevice(), m_swapchain.GetFormat(), m_renderPass);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Failed to create render pass");

    result = CreateGraphicPipeline(m_swapchain.GetRelatedDevice().GetDevice(),
        shadersCollector.GetVertexStaticObject().GetShaderModule(),
        shadersCollector.GetFragmentStaticObject().GetShaderModule(),
        m_pipelineLayout,
        m_renderPass,
        m_swapchain.GetExtent2D(),
        m_graphicsPipeline);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Failed to create graphics pipeline");

    m_framebuffers.resize(swapchain.GetImageViews().size());
    for (size_t i = 0; i < m_framebuffers.size(); ++i)
    {
        result = CreateFramebuffer(m_swapchain.GetRelatedDevice().GetDevice(),
            m_renderPass,
            swapchain.GetImageViews()[i],
            m_swapchain.GetExtent2D(),
            m_framebuffers[i]);
        if (result != VK_SUCCESS)
            throw std::runtime_error("Failed to create framebuffer!");
    }

    VkDescriptorBufferInfo descriptorBufferInfo = {};
    descriptorBufferInfo.buffer = m_transform.GetMatricesBuffer().GetBuffer();
    descriptorBufferInfo.offset = 0;
    descriptorBufferInfo.range = sizeof(Transform::Matrices);

    VkWriteDescriptorSet writeDescriptorSet = {};
    writeDescriptorSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    writeDescriptorSet.dstSet = m_descriptorSet;
    writeDescriptorSet.dstBinding = 0;
    writeDescriptorSet.dstArrayElement = 0;
    writeDescriptorSet.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    writeDescriptorSet.descriptorCount = 1;
    writeDescriptorSet.pBufferInfo = &descriptorBufferInfo;
    writeDescriptorSet.pImageInfo = nullptr;
    writeDescriptorSet.pTexelBufferView = nullptr;

    vkUpdateDescriptorSets(m_swapchain.GetRelatedDevice().GetDevice(), 1, &writeDescriptorSet, 0, nullptr);
}

StaticObjectPipeline::~StaticObjectPipeline()
{
    for (auto framebuffer : m_framebuffers)
        vkDestroyFramebuffer(m_swapchain.GetRelatedDevice().GetDevice(), framebuffer, nullptr);
    vkDestroyPipeline(m_swapchain.GetRelatedDevice().GetDevice(), m_graphicsPipeline, nullptr);
    vkDestroyRenderPass(m_swapchain.GetRelatedDevice().GetDevice(), m_renderPass, nullptr);
    vkDestroyPipelineLayout(m_swapchain.GetRelatedDevice().GetDevice(), m_pipelineLayout, nullptr);
    vkFreeDescriptorSets(m_swapchain.GetRelatedDevice().GetDevice(), m_descriptorPool, 1, &m_descriptorSet);
    vkDestroyDescriptorPool(m_swapchain.GetRelatedDevice().GetDevice(), m_descriptorPool, nullptr);
    vkDestroyDescriptorSetLayout(m_swapchain.GetRelatedDevice().GetDevice(), m_descriptorSetLayout, nullptr);
}

Swapchain& StaticObjectPipeline::GetRelatedSwapchain() const
{
    return m_swapchain;
}

Device& StaticObjectPipeline::GetRelatedDevice() const
{
    return m_swapchain.GetRelatedDevice();
}

VkDescriptorSetLayout StaticObjectPipeline::GetDescriptorSetLayout() const
{
    return m_descriptorSetLayout;
}

VkDescriptorPool StaticObjectPipeline::GetDescriptorPool() const
{
    return m_descriptorPool;
}

VkDescriptorSet StaticObjectPipeline::GetDescriptorSet() const
{
    return m_descriptorSet;
}

VkPipelineLayout StaticObjectPipeline::GetPipelineLayout() const
{
    return m_pipelineLayout;
}

VkRenderPass StaticObjectPipeline::GetRenderPass() const
{
    return m_renderPass;
}

VkPipeline StaticObjectPipeline::GetGraphicsPipeline() const
{
    return m_graphicsPipeline;
}

const std::vector<VkFramebuffer>& StaticObjectPipeline::GetFramebuffers() const
{
    return m_framebuffers;
}

Transform& StaticObjectPipeline::GetTransform()
{
    return m_transform;
}
}
