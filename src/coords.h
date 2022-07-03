#pragma once
#ifndef COORDS_H
#define COORDS_H

struct Coords
{
    Coords(int x = 0, int y = 0) : x(x), y(y){};

    int x;
    int y;

    Coords operator+(const Coords &other)
    {
        return Coords(this->x + other.x, this->y + other.y);
    }

    Coords operator-(const Coords &other)
    {
        return Coords(this->x - other.x, this->y - other.y);
    }

    void operator=(const Coords &other)
    {
        this->x = other.x;
        this->y = other.y;
    }

    void operator+=(const Coords &other)
    {
        this->x += other.x;
        this->y += other.y;
    }

    friend bool operator==(const Coords &val1, const Coords &val2)
    {
        return (val1.x == val2.x && val1.y == val2.y);
    }
};

#endif