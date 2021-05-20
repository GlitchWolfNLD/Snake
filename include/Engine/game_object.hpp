#pragma once
#include <SDL2/SDL.h>

namespace Engine
{
    //class representing every gameobject, every gameobject class must inherit from this class
    class GameObject
    {
    public:
        virtual void handleEvents(SDL_Event *e);

        virtual void update();

        virtual void render();
    };
}