#ifndef VT_WINDOW_INCLUDE_H
#define VT_WINDOW_INCLUDE_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>

namespace VT
{
class VTWindow
{
public:
    VTWindow(int width, int height, const std::string& title);
    virtual ~VTWindow();
    VTWindow(const VTWindow& other) = delete;
    VTWindow(VTWindow&& other) = delete;
    VTWindow& operator=(const VTWindow& other) = delete;
    VTWindow& operator=(VTWindow&& other) = delete;

    GLFWwindow* GetWindow();
    const GLFWwindow* GetWindow() const;

    const std::string& GetTitle() const;

private:
    GLFWwindow* m_window;
    std::string m_title;
};
}

#endif
