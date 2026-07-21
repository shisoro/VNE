#pragma once    
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

    void processInput();
    void update(double deltaTime);
    void render();
    void requestQuit();

    State state = State::Uninitialized;
};