#include "snake.h"

Snake::Snake(Coords limits) : limits(limits), dir(0, 0)
{
    snake_coords.push_back(Coords(limits.x / 2, limits.y / 2));
}

void Snake::draw(Coords board_start)
{
    for (int i = 1; i < snake_coords.size(); i++)
    {
        MOVE_CURSOR_TO_POS(board_start.y + snake_coords[i].y, board_start.x + snake_coords[i].x);
        printf("o");
    }

    MOVE_CURSOR_TO_POS(board_start.y + snake_coords[0].y, board_start.x + snake_coords[0].x);
    printf("O");
}

void Snake::setDir(int dir)
{
    switch (dir)
    {
    case 1:
        this->dir = Coords(0, -1);
        break;
    case 2:
        this->dir = Coords(1, 0);
        break;
    case 3:
        this->dir = Coords(0, 1);
        break;
    case 4:
        this->dir = Coords(-1, 0);
        break;
    }
}

void Snake::step()
{
    int lastSnakePosMoved = snake_coords.size();

    if (eaten)
    {
        lastSnakePosMoved--;
        eaten = false;
    }

    for (int i = lastSnakePosMoved; i > 0; i--)
    {
        snake_coords[i] = snake_coords[i - 1];
    }
    this->snake_coords[0] += this->dir;

    if(this->snake_coords[0].x >= limits.x)
    {
        this->snake_coords[0].x -= limits.x;
    }
    else if(this->snake_coords[0].x < 0)
    {
        this->snake_coords[0].x += limits.x;
    }
    
    if(this->snake_coords[0].y >= limits.y)
    {
        this->snake_coords[0].y -= limits.y;
    }
    else if(this->snake_coords[0].y < 0)
    {
        this->snake_coords[0].y += limits.y;
    }

}

bool Snake::collides(Coords obj, int start_ind)
{
    for (int i = start_ind; i < snake_coords.size(); i++)
    {
        if (snake_coords[i] == obj)
        {
            return true;
        }
    }

    return false;
}

void Snake::eat()
{
    this->snake_coords.push_back(this->snake_coords[this->snake_coords.size() - 1]);
    eaten = true;
}

Coords Snake::getHead()
{
    return this->snake_coords[0];
}
