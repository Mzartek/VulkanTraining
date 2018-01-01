#include <private/Window.h>

#include <stdexcept>

namespace VT
{
Window::Window(int width, int height, const std::string& title)
    : m_window(nullptr)
    , m_width(width)
    , m_height(height)
    , m_title(title)
{
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
    if (m_window == nullptr)
        throw std::runtime_error("Failed to create window");
}

Window::~Window()
{
    glfwDestroyWindow(m_window);
}

GLFWwindow* Window::GetWindow()
{
    return m_window;
}

const GLFWwindow* Window::GetWindow() const
{
    return m_window;
}

int Window::GetWidth() const
{
    return m_width;
}

int Window::GetHeight() const
{
    return m_height;
}

const std::string& Window::GetTitle() const
{
    return m_title;
}
}
