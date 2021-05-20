#include <iostream>
#include <Snake/snake.hpp>
#include <Engine/game_object.hpp>
#include <Engine/game.hpp>

int main()
{
    Engine::Game *game = new Engine::Game();
    game->init();

    SnakeGame::Snake *snake = new SnakeGame::Snake();
    snake->init(game);

    game->gameObjects.push_back(snake);

    while (game->isRunning)
    {
        game->handleEvents();
        game->update();
        game->render();
        SDL_Delay(150);
    }

    return 0;
}
