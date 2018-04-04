#include <private/Surface.h>

#include <stdexcept>

namespace VT
{
Surface::Surface(Instance& instance, int width, int height, const std::string& title, void* userPointer, GLFWwindowsizefun sizeCallback)
    : m_instance(instance)
    , m_window(nullptr)
    , m_surface(VK_NULL_HANDLE)
{
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (m_window == nullptr)
        throw std::runtime_error("Failed to create window");

    glfwSetWindowUserPointer(m_window, userPointer);
    glfwSetWindowSizeCallback(m_window, sizeCallback);

    VkResult result = glfwCreateWindowSurface(m_instance.GetInstance(), m_window, nullptr, &m_surface);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Failed to create surface");
}

Surface::~Surface()
{
    vkDestroySurfaceKHR(m_instance.GetInstance(), m_surface, nullptr);

    glfwDestroyWindow(m_window);
}

uint32_t Surface::GetWidth() const
{
    int width = 0;
    glfwGetWindowSize(m_window, &width, nullptr);

    return width;;
}

uint32_t Surface::GetHeight() const
{
    int height = 0;
    glfwGetWindowSize(m_window, nullptr, &height);

    return height;
}

Instance& Surface::GetRelatedInstance() const
{
    return m_instance;
}

GLFWwindow* Surface::GetWindow() const
{
    return m_window;
}

VkSurfaceKHR Surface::GetSurface() const
{
    return m_surface;
}
}
