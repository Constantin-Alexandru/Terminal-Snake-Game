#pragma once

#include "coords.h"
#include "../ANSI-Library/ansi_lib.h"
#include <vector>

class Snake
{
public:
    Snake(Coords limits = Coords());
    void draw(Coords board_start);
    void setDir(int dir);
    void step();
    bool collides(Coords obj, int start_ind = 0);
    void eat();

    Coords getHead();

private:
    std::vector<Coords> snake_coords;
    Coords limits;
    Coords dir;

    bool eaten = false;
};
