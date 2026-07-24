#pragma once

class Input
{
public:
    void beginFrame();      // フレーム状態の初期化
    void processEvents();

    bool quitRequested() const;
    bool advancePressed() const;

private:
    bool quitRequestedThisFrame = false;
    bool advancePressedThisFrame = false;
};