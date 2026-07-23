#include "Application.hpp"
#include <SDL3/SDL.h>
#include <chrono>
#include <iostream>
#include <thread>

namespace
{
    constexpr int windowWidth = 1280;
    constexpr int windowHeight = 720;

    constexpr float messageBoxMargin = 60.0f;
    constexpr float messageBoxHeight = 180.0f;
}

Application::~Application()
{
    cleanup();
}

// 設定の初期化
bool Application::initialize()
{
    if (state != State::Uninitialized)
    {
        std::cout << "Application initialized." 
                  << std::endl;

        return true;
    }

    // SDLの初期化
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        std::cerr << "Failed to initialize SDL: "
                  << SDL_GetError()
                  << std::endl;

        return false;
    }

    sdlInitialized = true;

    // SDLWindowの初期化
    window = SDL_CreateWindow(
        "NovelEngine",
        windowWidth,
        windowHeight,
        0
    );

    if (window == nullptr)
    {
        std::cerr << "Failed to create window: "
                  << SDL_GetError()
                  << std::endl;
        
        cleanup();
        return false;
    }

    // SDLRenderの初期化
    renderer = SDL_CreateRenderer(
        window, // 描画先のウィンドウ
        nullptr // 使用する描画ドライバー（nullptrの場合はSDLに任せる）
    );

    if (renderer == nullptr)
    {
        std::cerr << "Failed to create renderer: "
                  << SDL_GetError()
                  << std::endl;
        
        cleanup();
        return false;
    }

    // ブレンドモードに設定（透明時の色の混合処理を有効にする）
    if (!SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND))
    {
        std::cerr << "Failed to set render blend mode: "
                  << SDL_GetError()
                  << std::endl;
        
        cleanup();
        return false;
    }

    // BMP画像を背景として描画（SDLSurfaceの初期化）
    SDL_Surface* backgroundSurface =
        SDL_LoadBMP("assets/background.bmp");

    if (backgroundSurface == nullptr)
    {
        std::cerr << "Failed to load background image: "
                  << SDL_GetError()
                  << std::endl;

        cleanup();
        return false;
    }

    // SDLTextureの初期化
    backgroundTexture =
        SDL_CreateTextureFromSurface(
            renderer,
            backgroundSurface
        );

    if (backgroundTexture == nullptr)
    {
        std::cerr << "Failed to create background texture: "
                  << SDL_GetError()
                  << std::endl;
                
        SDL_DestroySurface(backgroundSurface);
        backgroundSurface = nullptr;

        cleanup();
        return false;
    }

    // SDLSurfaceの破棄
    SDL_DestroySurface(backgroundSurface);
    backgroundSurface = nullptr;

    // Stateを更新
    state = State::Initialized;

    std::cout << "Application initialized." << std::endl;    

    return true;
}

// 状態 Running の処理
void Application::run()
{
    if (state != State::Initialized)
    {
        std::cerr << "Application must be initialized before run()."
                  << std::endl;
        return;
    }

    state = State::Running;

    using Clock = std::chrono::steady_clock;

    constexpr double targetFramesPerSecond = 60.0;

    const std::chrono::duration<double> targetFrameDuration {
        1.0 / targetFramesPerSecond
    };

    auto previousTime = Clock::now();

    while (state == State::Running)
    {
        const auto frameStartTime = Clock::now();

        const std::chrono::duration<double> elapsed =
            frameStartTime - previousTime;

        const double deltaTime = elapsed.count();

        previousTime = frameStartTime;

        processEvents();
        update(deltaTime);
        render();

        if (state != State::Running)
        {
            break;
        }

        const auto frameEndTime = Clock::now();

        const auto frameProcessingTime =
            frameEndTime - frameStartTime;
        
        if (frameProcessingTime < targetFrameDuration)
        {
            const auto remainingTime =
                targetFrameDuration - frameProcessingTime;
            
            std::this_thread::sleep_for(remainingTime);
        }
    }
}

// 状態を見て終了処理を行う
void Application::shutdown()
{
    if (state == State::Uninitialized)
    {
        return;
    }

    cleanup();
    
    std::cout << "Application shut down." << std::endl;
}

// SDLを用いて入力などのイベントを受け取って処理する
void Application::processEvents()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_EVENT_QUIT)
        {
            requestQuit();
        }
    }
}

// フレームごとの状態を更新する
void Application::update(double deltaTime)
{
    static_cast<void>(deltaTime);
}

// 描画処理
void Application::render()
{
    // 背景
    SDL_SetRenderDrawColor(         // 描画色を設定する
        renderer,
        30, // red
        30, // green
        45, // blue
        255 // alpha（不透明度）
    );

    SDL_RenderClear(renderer);      // 背景を塗りつぶす（背景の初期化）

    SDL_RenderTexture(
        renderer,
        backgroundTexture,
        nullptr,
        nullptr
    );

    // メッセージウィンドウ
    const SDL_FRect messageBox{
        messageBoxMargin,                   // 長方形の左上のx座標
        static_cast<float>(windowHeight)    // 長方形の左上のy座標
            - messageBoxMargin
            - messageBoxHeight,     
        static_cast<float>(windowWidth)     // 長方形の幅
            - messageBoxMargin * 2.0f,  
        messageBoxHeight                    // 長方形の高さ
    };

    SDL_SetRenderDrawColor(
        renderer,
        10,
        10,
        20,
        200
    );

    SDL_RenderFillRect(
        renderer,
        &messageBox
    );

    SDL_RenderPresent(renderer);    // 完成した結果を画面へ表示
}

// 終了を要求する
void Application::requestQuit()
{
    if (state != State::Running)
    {
        return;
    }

    std::cout << "Quit requested." << std::endl;
    
    state = State::Initialized;
}

void Application::cleanup()
{
    if (backgroundTexture != nullptr)
    {
        SDL_DestroyTexture(backgroundTexture);
        backgroundTexture = nullptr;
    }

    if (renderer != nullptr)
    {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }

    if (window != nullptr)
    {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    if (sdlInitialized)
    {
        SDL_Quit();
        sdlInitialized = false;
    }

    state = State::Uninitialized;
}