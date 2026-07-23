#pragma once

struct SDL_Window;
struct SDL_Renderer;  
struct SDL_Texture;

class Graphics
{
public:
    Graphics() = default;
    ~Graphics();

    Graphics(const Graphics&) = delete;
    Graphics& operator=(const Graphics&) = delete;

    Graphics(Graphics&&) = delete;
    Graphics& operator=(Graphics&&) = delete;

    bool initialize();
    void render();
    void shutdown();

private:
    void cleanup();

    bool sdlInitialized = false;

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Texture* backgroundTexture = nullptr;
};