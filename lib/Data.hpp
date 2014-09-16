#ifndef DATA_HPP
#define DATA_HPP

#include <iostream>

unsigned const TILE_SIZE = 32;
float const SCALE = 32.f;
float const UPDATES_PER_SECOND = 60;

enum class Movement
{
    Idle,
    Left,
    Right,
};

#endif
