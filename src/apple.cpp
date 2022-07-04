#include "apple.h"

Apple::Apple(Coords limits) : coords(), x_distribution(0, limits.x - 1), y_distribution(0, limits.y - 2)
{
    std::random_device device;
    std::mt19937 rng(device());

    this->rng = rng;

    spawn();
};

void Apple::spawn()
{
    coords = Coords(x_distribution(rng), y_distribution(rng));
}

void Apple::draw(Coords board_start)
{
    SET_8_VALUE_COLOUR(TXT_GREEN);
    MOVE_CURSOR_TO_POS(board_start.y + coords.y, board_start.x + coords.x);

    printf("X");
    SET_8_VALUE_COLOUR(TXT_WHITE);
}

Coords Apple::getCoords()
{
    return this->coords;
}