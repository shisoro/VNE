#pragma once    
class Application
{
public:
    bool initialize();
    void run();
    void shutdown();

private:
    bool initialized = false;
    bool running = false;    
};