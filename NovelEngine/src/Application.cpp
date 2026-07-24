#include "Application.hpp"
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

    if (!graphics.initialize())
    {
        std::cerr << "Failed to initialize graphics."
                  << std::endl;

        return false;
    }

    // Stateを更新
    state = State::Initialized;

    std::cout << "Application initialized." << std::endl;    

    std::cout << "Current text: " 
              << scenario.currentText()
              << std::endl;

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

        input.beginFrame();
        input.processEvents();

        processInput(); // 入力結果をApplicationが解釈

        if (state != State::Running)
        {
            break;
        }

        update(deltaTime);
        render();        

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

    graphics.shutdown();

    state = State::Uninitialized;
    
    std::cout << "Application shut down." << std::endl;
}

// SDLを用いて入力などのイベントを受け取って処理する
void Application::processInput()
{

    if (input.quitRequested())
    {
        requestQuit();
        return;
    }

    if (input.advancePressed())
    {
        if (scenario.advance())
        {
            std::cout << "Current text: "
                      << scenario.currentText()
                      << std::endl;
        }
        else
        {
            std::cout << "Reached the end of the scenario."
                      << std::endl;
        }
    }
}

// フレームごとの状態を更新する
void Application::update(double deltaTime)
{
    static_cast<void>(deltaTime);
}

// 描画を要求する
void Application::render()
{
    graphics.render();
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