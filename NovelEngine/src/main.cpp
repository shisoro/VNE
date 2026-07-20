#include "Application.hpp"

int main()
{
    Application app;

    app.initialize();
    app.run();
    app.shutdown();
    
    return 0;
}