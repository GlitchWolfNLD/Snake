#include <Snake/snake.hpp>
#include <random>

using namespace SnakeGame;
using namespace Engine;

//inits the snake
void Snake::init(Game *game)
{
    this->game = game;

    rect.x = x;
    rect.y = y;
    rect.w = rect.h = SIZE - 1;

    //spawn first food
    spawnFood();
}

void Snake::handleEvents(SDL_Event *e)
{
    switch (e->type)
    {
    case SDL_KEYDOWN:
        switch (e->key.keysym.sym)
        {
            case SDLK_UP:
                if(dir != down) dir = up;
                break;
            case SDLK_DOWN:
                if(dir != up) dir = down;
                break;
            case SDLK_LEFT:
                if(dir != right) dir = left;
                break;
            case SDLK_RIGHT:
                if(dir != left) dir = right;
                break;
        }
    }
}

//updates the snake with the new input
void Snake::update()
{
    //update all children
    std::vector<SDL_Rect> temp;
    temp = children;
    for (int i = 0; i < children.size(); i++)
    {
        if (i == 0)
        {
            temp[i].x = x;
            temp[i].y = y;
        }
        else
        {
            temp[i].x = children[i - 1].x;
            temp[i].y = children[i - 1].y;
        }
    }

    children = temp;

    switch (dir)
    {
        case right:
            x += STEP;
            break;
        case left:
            x -= STEP;
            break;
        case up:
            y -= STEP;
            break;
        case down:
            y += STEP;
            break;
    }

    //grow if there is a collision with the food
    if(food.x == x && food.y == y)
    {
        //grow by 1
        grow();
        //move food to other position;
        spawnFood();
    }

    //game over
    int w, h;
    SDL_GetWindowSize(game->window, &w, &h);
    if (x > w || x < 0 || y < 0 || y > h)
    {
        game->isRunning = false;
    }

    //check collisions with tail
    for(int i = 0; i < children.size(); i++)
    {
        switch(dir){
            case left:
                if (x-STEP == children[i].x && y == children[i].y) game->isRunning = false;
                break;
            case right:
                if (x+STEP == children[i].x && y == children[i].y) game->isRunning = false;
                break;
            case up:
                if (x == children[i].x && y-STEP == children[i].y) game->isRunning = false;
                break;
            case down:
                if (x == children[i].x && y+STEP == children[i].y) game->isRunning = false;
                break;
        }
    }
}

//renders the snake to the screen
void Snake::render()
{
    //set snake color
    SDL_SetRenderDrawColor(game->renderer, snakeColor[0], snakeColor[1], snakeColor[2], snakeColor[3]);

    //draw children
    for (int i = 0; i < children.size(); ++i)
    {
        SDL_RenderFillRect(game->renderer, &children[i]);
    }

    //draw head
    rect.x = x;
    rect.y = y;
    SDL_RenderFillRect(game->renderer, &rect);

    //render food
    SDL_SetRenderDrawColor(game->renderer, foodColor[0], foodColor[1], foodColor[2], foodColor[3]);
    SDL_RenderFillRect(game->renderer, &food);
}

//grows the snake by 1
void Snake::grow()
{
    SDL_Rect child;
    int x, y;
    if (children.size() > 0)
    {
        //copy last child's position
        x = children[children.size() - 1].x;
        y = children[children.size() - 1].y;
    }
    else
    {
        //copy head's position
        x = this->x;
        y = this->y;
    }

    child.x = x;
    child.y = y;
    child.w = child.h = SIZE - 1;

    children.push_back(child);

    size++;
}

//spawns the food at a random position
void Snake::spawnFood()
{
    int w,h;
    SDL_GetWindowSize(game->window, &w, &h);
    food.x = randomRangeStep(0, w - SIZE, STEP);
    food.y = randomRangeStep(0, h - SIZE, STEP);
    food.w = food.h = SIZE - 1;
}

int Snake::randomRange(int minValue, int maxValue)
{
    return rand() % maxValue + minValue;
}

int Snake::randomRangeStep(int minValue, int maxValue, int step)
{
    return randomRange(minValue / step, maxValue / step) * step;
}
