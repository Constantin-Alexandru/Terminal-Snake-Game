#pragma once

#include "coords.h"
#include "../ANSI-Library/ansi_lib.h"

#include <random>
#include <stdio.h>

class Apple{
public:
    Apple(Coords limits = Coords());
    void spawn();
    void draw(Coords board_spawn);
    Coords getCoords();
private:
    Coords coords;
    Coords limits;

    std::mt19937 rng;
    std::uniform_int_distribution<int> x_distribution;
    std::uniform_int_distribution<int> y_distribution;
};
