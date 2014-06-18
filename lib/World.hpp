#ifndef WORLD_HPP
#define WORLD_HPP

#include <Box2D/Box2D.h>
#include "lib/Grid.hpp"

class World
{
    public:
        World();
        void update(sf::Time dt);
        void render(sf::RenderTarget& target, sf::Time dt) const;

    private:
        Grid mGrid;
        b2World mPhysics;

        GameObject test;
};

#endif
