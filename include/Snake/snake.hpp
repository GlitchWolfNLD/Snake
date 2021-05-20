#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include <Engine/game.hpp>
#include <Engine/game_object.hpp>

#pragma once

namespace SnakeGame
{
    enum Direction
    {
        up,
        down,
        left,
        right
    };

    //this class represents the snake (the player)
    class Snake : public Engine::GameObject
    {
        //size of the snake head
        const int SIZE = 25;

        //the change in x or y in one frame
        const int STEP = SIZE;

        //the color of the snake (green)
        const int snakeColor[4] = {11, 156, 49, 255};

        //color of the food (blue)
        const int foodColor[4] = {0, 0, 255, 255};

    protected:
        //snake's head rectangle
        SDL_Rect rect;

        SDL_Rect food;

        Engine::Game *game;

        //snake's head position
        int x = 400, y = 300;

        std::vector<SDL_Rect> children;

        Direction dir = right;

        int size = 0;

    public:
        void init(Engine::Game *game);

        void handleEvents(SDL_Event *e) override;

        void render() override;

        void update() override;

        void grow();

        void spawnFood();

        int randomRange(int minValue, int maxValue);

        int randomRangeStep(int minValue, int maxValue, int step);
    };
}