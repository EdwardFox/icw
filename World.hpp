#ifndef WORLD_HPP
#define WORLD_HPP

#include "Grid.hpp"

class World
{
    public:
        World();
        void update(sf::Time dt);
        void render(sf::RenderTarget& target, sf::Time dt) const;

    private:
        Grid mGrid;
};

#endif
