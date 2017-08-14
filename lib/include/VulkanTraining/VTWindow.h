#ifndef VT_WINDOW_INCLUDE_H
#define VT_WINDOW_INCLUDE_H

#include "VTExport.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>

namespace VT
{
class LIB_INTERFACE Window
{
public:
    Window(int width, int height, const std::string& title);
    virtual ~Window();
    Window(const Window& other) = delete;
    Window(Window&& other) = delete;
    Window& operator=(const Window& other) = delete;
    Window& operator=(Window&& other) = delete;

    GLFWwindow* GetWindow();
    const GLFWwindow* GetWindow() const;

    int GetWidth() const;
    int GetHeight() const;
    const std::string& GetTitle() const;

private:
    GLFWwindow* m_window;

    int m_width;
    int m_height;
    std::string m_title;
};
}

#endif
