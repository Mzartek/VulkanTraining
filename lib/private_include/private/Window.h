#ifndef VT_WINDOW_INCLUDE_H
#define VT_WINDOW_INCLUDE_H

#include "NonCopyableObject.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>
#include <functional>

namespace VT
{
class Window : public NonCopyableObject
{
public:
    Window(int width, int height, const std::string& title, void* userPointer, GLFWwindowsizefun resizeFunction);
    ~Window() override;

    GLFWwindow* GetWindow() const;

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
