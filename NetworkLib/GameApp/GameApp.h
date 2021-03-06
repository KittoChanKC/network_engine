#pragma once

#define SDL_MAIN_HANDLED
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#include <SDL.h>

class GameApp
{
public:
    virtual ~GameApp();

    bool getInputKey(SDL_Keycode key)
    {
        auto s = SDL_GetScancodeFromKey(key);
        return ImGui::GetIO().KeysDown[s];
    }


    void         run();
    virtual void onUpdate(float deltaTime) {}
    virtual void onNetWork(){};
    virtual void onEvent(SDL_Event& ev){};
    virtual void onImGui(){};
};

namespace app {
SDL_Window* GetWindow();
}
