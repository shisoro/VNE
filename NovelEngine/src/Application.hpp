#pragma once    
class Application
{
public:
    bool initialize();
    void run();
    void shutdown();

private:
    void processInput();
    void update();
    void render();

    bool initialized = false;
    bool running = false;    
};