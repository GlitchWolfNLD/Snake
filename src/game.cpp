#include <Engine/game.hpp>

using namespace Engine;

void Game::init()
{
    SDL_Init(SDL_INIT_VIDEO);

    this->window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if (window != NULL)
    {
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        isRunning = true;
    }
}

void Game::handleEvents()
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        switch (e.type)
        {
            case SDL_QUIT:
                isRunning = false;
                break;
            default:
                for(int i = 0; i < gameObjects.size(); ++i) gameObjects[i]->handleEvents(&e);
                break;
        }
    }
}

void Game::update() 
{
    for(int i = 0; i < gameObjects.size(); i++)
    {
        gameObjects[i]->update();
    }
}

void Game::render()
{
    //Black background color
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    //Render all objects
    for (int i = 0; i < gameObjects.size(); i++)
    {
        gameObjects[i]->render();
    }

    SDL_RenderPresent(renderer);
}