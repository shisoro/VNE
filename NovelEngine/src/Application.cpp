#include "Application.hpp"
#include <iostream>

bool Application::initialize()
{
    if (state != State::Uninitialized)
    {
        std::cout << "Application initialized." << std::endl;
        return true;
    }

    std::cout << "Application initialized." << std::endl;

    state = State::Initialized;
    return true;
}

void Application::run()
{
    if (state != State::Initialized)
    {
        std::cerr << "Application must be initialized before run()."
                  << std::endl;
        return;
    }

    state = State::Running;

    int frameCount = 0;

    while (state == State::Running)
    {
        std::cout << "Frame: " << frameCount << std::endl;

        processInput();
        update();
        render();

        ++frameCount;

        if (frameCount >= 3)
        {
            requestQuit();
        }
    }
}

void Application::shutdown()
{
    if(state == State::Uninitialized)
    {
        return;
    }

    state = State::Uninitialized;
    
    std::cout << "Application shut down." << std::endl;
}

void Application::processInput()
{
    std::cout << "Process input." << std::endl;    
}

void Application::update()
{
    std::cout << "Update game state." << std::endl;
}

void Application::render()
{
    std::cout << "Render frame." << std::endl;
}

void Application::requestQuit()
{
    if (state != State::Running)
    {
        return;
    }

    std::cout << "Quit requested." << std::endl;
    
    state = State::Initialized;
}