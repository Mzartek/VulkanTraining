#include <VulkanTraining/GameMode.h>

#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>

#include <iostream>

constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;

namespace po = boost::program_options;
namespace fs = boost::filesystem;

class HelloTriangleApplication : public VT::GameMode
{
public:
    HelloTriangleApplication(const std::string& shadersPath)
        : GameMode(WIDTH, HEIGHT, "HelloTriangleApplication", shadersPath)
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

int main(int ac, char** av)
{
    po::options_description desc("Options");
    desc.add_options()
        ("help", "Produce help message")
        ("shaders", po::value<std::string>(), "Indicate shaders path")
    ;

    po::variables_map vm;
    po::store(po::parse_command_line(ac, av, desc), vm);
    po::notify(vm);

    if (vm.count("help"))
    {
        std::cout << desc << std::endl;
        return EXIT_FAILURE;
    }

    if (!vm.count("shaders"))
    {
        std::cerr << "Missing shaders path" << std::endl;
        return EXIT_FAILURE;
    }

    const fs::path shadersPath = fs::path(vm["shaders"].as<std::string>());
    HelloTriangleApplication* app = new HelloTriangleApplication(shadersPath.string());

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
