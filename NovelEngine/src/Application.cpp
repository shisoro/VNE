#include "Application.hpp"
#include <iostream>

void Application::initialize()
{
    std::cout << "Application initialized." << std::endl;
}

void Application::run()
{
    std::cout << "Application running." << std::endl;
}

void Application::shutdown()
{
    std::cout << "Application shut down." << std::endl;
}