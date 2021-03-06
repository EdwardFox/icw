#ifndef DATA_HPP
#define DATA_HPP

#include <iostream>

unsigned const TILE_SIZE = 32;
float const SCALE = 32.f;
float const UPDATES_PER_SECOND = 60;
std::string const DEFAULT_FONT = "media/fonts/Arial.ttf";

enum class Movement
{
    Idle,
    Left,
    Right,
};

enum class Collision
{
    Top,
    Bottom,
    Left,
    Right,
    None
};

enum class Contact
{
    PreSolve,
    Begin,
    End,
    PostSolve
};

#endif
