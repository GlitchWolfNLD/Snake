#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include <Engine/game_object.hpp>

#pragma once

namespace Engine
{
    //abstract class for all game related functions
    class Game
    {
    public:
        SDL_Renderer *renderer;
        SDL_Window *window;

        bool isRunning = false;

        std::vector<GameObject*> gameObjects;

    public:
        void init();

        void handleEvents();

        void update();

        void render();
    };
}