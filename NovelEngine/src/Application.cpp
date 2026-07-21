#include "Application.hpp"
#include <SDL3/SDL.h>
#include <chrono>
#include <iostream>

bool Application::initialize()
{
    if (state != State::Uninitialized)
    {
        std::cout << "Application initialized." << std::endl;
        return true;
    }

    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        std::cerr << "Failed to initialize SDL: "
                  << SDL_GetError()
                  << std::endl;

        return false;
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

    using Clock = std::chrono::steady_clock;

    auto previousTime = Clock::now();

    int frameCount = 0;

    while (state == State::Running)
    {
        const auto currentTime = Clock::now();

        const std::chrono::duration<double> elapsed =
            currentTime - previousTime;

        const double deltaTime = elapsed.count();

        previousTime = currentTime;

        std::cout << "--- Frame " << frameCount << " ---" << std::endl;

        processInput();
        update(deltaTime);
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

    SDL_Quit();

    state = State::Uninitialized;
    
    std::cout << "Application shut down." << std::endl;
}

void Application::processInput()
{
    std::cout << "Process input." << std::endl;    
}

void Application::update(double deltaTime)
{
    std::cout << "Update game state. deltaTime = " 
              << deltaTime
              << " seconds."          
              << std::endl;
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