#include "Application.hpp"
#include <SDL3/SDL.h>
#include <chrono>
#include <iostream>
#include <thread>

// 設定の初期化
bool Application::initialize()
{
    if (state != State::Uninitialized)
    {
        std::cout << "Application initialized." 
                  << std::endl;

        return true;
    }

    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        std::cerr << "Failed to initialize SDL: "
                  << SDL_GetError()
                  << std::endl;

        return false;
    }

    window = SDL_CreateWindow(
        "NovelEngine",
        1280,
        720,
        0
    );

    if (window == nullptr)
    {
        std::cerr << "Failed to create window: "
                  << SDL_GetError()
                  << std::endl;
        
        SDL_Quit();
        return false;
    }

    renderer = SDL_CreateRenderer(
        window, // 描画先のウィンドウ
        nullptr // 使用する描画ドライバー（nullptrの場合はSDLに任せる）
    );

    if (renderer == nullptr)
    {
        std::cerr << "Failed to create renderer: "
                  << SDL_GetError()
                  << std::endl;
        
        SDL_DestroyWindow(window);
        window = nullptr;

        SDL_Quit();
        return false;
    }

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

    SDL_Quit();

    state = State::Uninitialized;
    
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
    SDL_SetRenderDrawColor(         // 描画色を設定する
        renderer,
        30, // red
        30, // green
        45, // blue
        255 // alpha（不透明度）
    );

    SDL_RenderClear(renderer);      // 背景を塗りつぶす（背景の初期化）
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