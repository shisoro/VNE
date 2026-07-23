#include "Graphics.hpp"
#include <SDL3/SDL.h>
#include <iostream>

namespace
{
    constexpr int windowWidth = 1280;
    constexpr int windowHeight = 720;

    constexpr float messageBoxMargin = 60.0f;
    constexpr float messageBoxHeight = 180.0f;
}

Graphics::~Graphics()
{
    cleanup();
}

bool Graphics::initialize()
{
    if (sdlInitialized)
    {
        std::cout << "Graphics is already initialized." 
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

    std::cout << "Application initialized." << std::endl;    

    return true;
}

// 描画処理
void Graphics::render()
{
    if (renderer == nullptr)
    {
        return;
    }

    // 背景
    SDL_SetRenderDrawColor(         // 描画色を設定する
        renderer,
        30, // red
        30, // green
        45, // blue
        255 // alpha（不透明度）
    );

    SDL_RenderClear(renderer);      // 背景を塗りつぶす（背景の初期化）

    if (backgroundTexture != nullptr)
    {
        SDL_RenderTexture(
            renderer,
            backgroundTexture,
            nullptr,
            nullptr
        );
    }
    

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

// 状態を見て終了処理を行う
void Graphics::shutdown()
{
    if (!sdlInitialized)
    {
        return;
    }

    cleanup();
    
    std::cout << "Graphics shut down." << std::endl;
}

// 異常時の対応処理
void Graphics::cleanup()
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
}