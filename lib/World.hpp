#ifndef WORLD_HPP
#define WORLD_HPP

#include <Box2D/Box2D.h>
#include "lib/Grid.hpp"
#include "lib/ResourceHolder.hpp"
#include "lib/Camera.hpp"
#include "lib/PhysicsContactListener.hpp"
#include "lib/Map.hpp"

class World
{
public:
    World();

    void initializeTextures();

    void update( sf::Time dt, sf::Vector2u windowSize );

    void render( sf::RenderTarget& target, sf::Time dt, sf::Vector2u windowSize ) const;

    void loadMap( std::string path );

    GameObject* createGameObject( sf::Vector2f position, sf::Vector2f size );

private:

    void createPlayer();

    void createPlayerAnimations();

    void createPlayerStates();

    // Resources
    ResourceHolder<sf::Texture, std::string> mTextures;

    // Game World
    std::vector<std::unique_ptr<Grid>> mGrids;
    std::unordered_map<std::string, Map> mMaps;
    std::vector<std::unique_ptr<GameObject>> mObjects;
    std::vector<std::unique_ptr<GameObject>> mObjectsToCreate;
    b2World mPhysics;
    Camera mCamera;
    GameObject* mPlayer;
    Map* mActiveMap;
    Grid* mWorldGrid;

    PhysicsContactListener mListener;
};

#endif
