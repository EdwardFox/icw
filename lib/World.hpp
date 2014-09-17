#ifndef WORLD_HPP
#define WORLD_HPP

#include <Box2D/Box2D.h>
#include "lib/Grid.hpp"
#include "lib/ResourceHolder.hpp"
#include "lib/Camera.hpp"
#include "lib/PhysicsContactListener.hpp"

class World
{
public:
    World();

    void initializeTextures();

    void update( sf::Time dt );

    void render( sf::RenderTarget& target, sf::Time dt, sf::Vector2u windowSize ) const;

private:
    void createPlayer();

    void createPlayerAnimations();

    void createPlayerStates();

    // Resources
    ResourceHolder<sf::Texture, std::string> mTextures;

    // Game World
    Grid mGrid;
    b2World mPhysics;
    Camera mCamera;
    GameObject mPlayer;

    PhysicsContactListener mListener;
};

#endif
