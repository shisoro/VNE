#include "Application.hpp"
#include <iostream>

bool Application::initialize()
{
    if (initialized)
    {
        std::cout << "Application initialized." << std::endl;
        return true;
    }

    std::cout << "Application initialized." << std::endl;

    initialized = true;
    return true;
}

void Application::run()
{
    if (!initialized)
    {
        std::cerr << "Application must be initialized before run()."
                  << std::endl;
        return;
    }

    running = true;

    int frameCount = 0;

    while (running)
    {
        std::cout << "Frame: " << frameCount << std::endl;

        ++frameCount;

        if (frameCount >= 3)
        {
            running = false;
        }
    }
}

void Application::shutdown()
{
    if(!initialized)
    {
        return;
    }

    running = false;
    initialized = false;
    
    std::cout << "Application shut down." << std::endl;
}