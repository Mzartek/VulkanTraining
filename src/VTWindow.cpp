#include "VTWindow.h"

#include <stdexcept>

namespace VT
{
VTWindow::VTWindow(int width, int height, const std::string& title)
    : m_window(nullptr)
    , m_title(title)
{
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    m_window = glfwCreateWindow(width, height, m_title.c_str(), nullptr, nullptr);
    if (m_window == nullptr)
        throw std::runtime_error("Failed to create window");
}

VTWindow::~VTWindow()
{
    glfwDestroyWindow(m_window);
}

GLFWwindow* VTWindow::GetWindow()
{
    return m_window;
}

const GLFWwindow* VTWindow::GetWindow() const
{
    return m_window;
}

const std::string& VTWindow::GetTitle() const
{
    return m_title;
}
}
