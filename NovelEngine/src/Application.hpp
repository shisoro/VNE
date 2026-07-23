#pragma once    

struct SDL_Window;
struct SDL_Renderer;  

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
    SDL_Renderer* renderer = nullptr;
};