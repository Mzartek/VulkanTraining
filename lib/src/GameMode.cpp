#include <VulkanTraining/GameMode.h>

#include <private/Drawables/StaticObjectDrawable.h>

#include <cassert>

namespace
{
#ifdef NDEBUG
constexpr bool enableValidationLayers = false;
#else
constexpr bool enableValidationLayers = true;
#endif

const std::vector<VT::StaticObjectPipeline::Vertex> vertices =
{
    {{ -0.25f, -0.25f, 0.25f }, { 0.0f, 0.0f }},
    {{ 0.25f, -0.25f, 0.25f }, { 0.0f, 1.0f }},
    {{ -0.25f, 0.25f, 0.25f }, { 1.0f, 0.0f }},
    {{ 0.25f, 0.25f, 0.25f }, { 1.0f, 1.0f }}
};

const std::vector<VT::StaticObjectPipeline::Index> indices = { 0, 1, 2, 2, 1, 3 };
}

namespace VT
{
GameMode::GameMode(const std::string& title, winid_t winId, SurfacePlatform surfacePlatform, const std::string& shadersPath)
    : m_instance(nullptr)
    , m_window(nullptr)
    , m_surface(nullptr)
    , m_physicalDevice(nullptr)
    , m_device(nullptr)
    , m_shadersCollector(nullptr)
    , m_swapchain(nullptr)
    , m_staticObjectPipeline(nullptr)
    , m_staticObjectDrawable(nullptr)
{
    m_instance = new Instance(title, enableValidationLayers);
    assert(m_instance);

    m_surface = new Surface(*m_instance, winId, surfacePlatform);
    assert(m_surface);

    m_physicalDevice = new PhysicalDevice(*m_instance);
    assert(m_physicalDevice);

    m_device = new Device(*m_physicalDevice, *m_surface, enableValidationLayers);
    assert(m_device);

    m_shadersCollector = new ShadersCollector(*m_device, shadersPath);
    assert(m_shadersCollector);

    CreateSwapchain();
}

GameMode::~GameMode()
{
    DeleteSwapchain();

    delete m_shadersCollector;
    delete m_device;
    delete m_physicalDevice;
    delete m_surface;
    delete m_instance;
}

void GameMode::Draw()
{
    try
    {
        m_swapchain->LoadNextImage();
    }
    catch (SwapchainOutOfDateException& ex)
    {
    }

    m_staticObjectDrawable->Draw();

    m_swapchain->PresentImage();
}

void GameMode::UpdateSwapchain()
{
    RecreateSwapchain();
}

void GameMode::CreateSwapchain()
{
    m_swapchain = new Swapchain(*m_device);
    assert(m_swapchain);

    m_staticObjectPipeline = new StaticObjectPipeline(*m_swapchain, *m_shadersCollector);
    assert(m_staticObjectPipeline);

    m_staticObjectDrawable = new StaticObjectDrawable(*m_staticObjectPipeline, vertices, indices);
    assert(m_staticObjectDrawable);
}

void GameMode::DeleteSwapchain()
{
    for (VkQueue transferQueue : m_device->GetTransferQueues())
        vkQueueWaitIdle(transferQueue);
    for (VkQueue graphicsQueue : m_device->GetGraphicsQueues())
        vkQueueWaitIdle(graphicsQueue);
    for (VkQueue computeQueue : m_device->GetComputeQueues())
        vkQueueWaitIdle(computeQueue);
    for (VkQueue presentQueue : m_device->GetPresentQueues())
        vkQueueWaitIdle(presentQueue);

    delete m_staticObjectDrawable;
    delete m_staticObjectPipeline;
    delete m_swapchain;
}

void GameMode::RecreateSwapchain()
{
    DeleteSwapchain();
    CreateSwapchain();
}
}
