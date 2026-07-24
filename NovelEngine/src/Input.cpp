#include "Input.hpp"
#include <SDL3/SDL.h>

void Input::beginFrame()
{
    quitRequestedThisFrame = false;
    advancePressedThisFrame = false;
}

void Input::processEvents()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_EVENT_QUIT)
        {
            quitRequestedThisFrame = true;
        }

        if (event.type == SDL_EVENT_KEY_DOWN)
        {
            if (event.key.repeat)
            {
                continue;
            }

            if (event.key.scancode == SDL_SCANCODE_ESCAPE)
            {
                quitRequestedThisFrame = true;
            }

            if (event.key.scancode == SDL_SCANCODE_SPACE)
            {
                advancePressedThisFrame = true;
            }
        }
    }
}

// 末尾のconstは、この関数はInputオブジェクトの状態を変更しないという意味
bool Input::quitRequested() const   
{
    return quitRequestedThisFrame;
}

bool Input::advancePressed() const
{
    return advancePressedThisFrame;
}