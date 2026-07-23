#pragma once    

struct SDL_Window;
struct SDL_Renderer;  
struct SDL_Texture;

class Application
{
public:
    Application() = default;
    ~Application();

    // コピーコンストラクタの禁止（Application app2 = app1;）
    Application(const Application&) = delete;
    // コピー代入の禁止（Application app1, app2; app2 = app1;）
    Application& operator=(const Application&) = delete;

    // ムーブの禁止（Application app2 = std::move(app1);）
    Application(Application&&) = delete;
    Application& operator=(Application&&) = delete;

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
    void cleanup();

    State state = State::Uninitialized;

    bool sdlInitialized = false;

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Texture* backgroundTexture = nullptr;
};