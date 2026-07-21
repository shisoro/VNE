#include <SDL3/SDL_main.h>

#include "Application.hpp"

int main(int argc, char* argv[])
{
    Application app;

    if(!app.initialize())
    {
        return 1;
    }
    
    app.run();
    app.shutdown();

    return 0;
}