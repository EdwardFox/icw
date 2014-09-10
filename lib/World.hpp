#ifndef WORLD_HPP
#define WORLD_HPP

#include <Box2D/Box2D.h>
#include "lib/Grid.hpp"
#include "lib/ResourceHolder.hpp"

class World
{
    public:
        World();

        void initializeTextures();

        void update(sf::Time dt);
        void render(sf::RenderTarget& target, sf::Time dt) const;

    private:
        // Resources
        ResourceHolder<sf::Texture, std::string> mTextures;

        // Game World
        Grid mGrid;
        b2World mPhysics;

        GameObject test;
};

#endif
