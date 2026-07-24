#pragma once    

#include "Graphics.hpp"
#include "Input.hpp"

class Application
{
public:
    Application() = default;
    ~Application() = default;

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

    void processInput();
    void update(double deltaTime);
    void render();
    void requestQuit();

    State state = State::Uninitialized;

    Graphics graphics;  // 所有者と同じオブジェクトは値として持つ
    Input input;
};