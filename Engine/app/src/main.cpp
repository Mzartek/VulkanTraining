#include <VulkanTraining/GameMode.h>

#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>

#include <iostream>

namespace po = boost::program_options;
namespace fs = boost::filesystem;

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
    VT::GameMode* app = new VT::GameMode(800, 600, "HelloTriangle", shadersPath.string());

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
