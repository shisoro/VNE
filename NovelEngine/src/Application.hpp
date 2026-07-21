#pragma once    

struct SDL_Window;  

class Application
{
public:
    bool initialize();
    void run();
    void shutdown();

private:
    enum class State
    {
        Uninitialized,
        Initialized,
        Running
    };

    void processEvents();
    void update(double deltaTime);
    void render();
    void requestQuit();

    State state = State::Uninitialized;
    SDL_Window* window = nullptr;
};