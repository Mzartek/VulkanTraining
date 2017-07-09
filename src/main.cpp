#include "GameMode.h"

#include <iostream>

constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;

class HelloTriangleApplication : public VT::GameMode
{
public:
    HelloTriangleApplication()
        : GameMode(WIDTH, HEIGHT, "HelloTriangleApplication")
    {
    }

    void Init() override
    {
        std::cout << "Init" << std::endl;
    }

    void MainLoop() override
    {
    }

    void CleanUp() override
    {
        std::cout << "CleanUp" << std::endl;
    }
};

int main()
{
    HelloTriangleApplication* app = new HelloTriangleApplication;

    try
    {
        app->Launch();
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    delete app;

    return EXIT_SUCCESS;
}
