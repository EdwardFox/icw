#ifndef WORLD_HPP
#define WORLD_HPP

#include <Box2D/Box2D.h>
#include "lib/Grid.hpp"
#include "lib/ResourceHolder.hpp"
#include "lib/Camera.hpp"
#include "lib/PhysicsContactListener.hpp"
#include "lib/Map.hpp"
#include "lib/gameobjects/GameObjectFactory.hpp"

/**
* Class that contains and manages all objects that make up the game world
*/
class World
{
public:

    /**
    * Initializes variables and sets up the basic world
    */
    World();

    /**
    * Loads textures
    * TODO: Replace this function by making game objects take care of loading the needed textures on their own (similar to the map loading)
    */
    void initializeTextures();

    /**
    * Updates the world and all its inhabitants
    *
    * sf::Time dt   - Time since last update
    * sf::Vector2u  - The current window size
    */
    void update( sf::Time dt, sf::Vector2u windowSize );

    /**
    * Renders the world
    *
    * sf::RenderTarget& target - Reference to the window onto which will be drawn
    * sf::Time dt - Time since last render
    */
    void render( sf::RenderTarget& target, sf::Time dt ) const;

    /**
    * Loads the given map into memory and fills all the layers
    *
    * std::string path - The path to the map to load
    */
    void loadMap( std::string path );

    /**
    * Creates a new game object, handled by the world. New objects are first put
    * into a separate vector to avoid increasing the object-vectors size (during iteration)
    * and possibly triggering a reallocation of memory, invalidating all iterators
    * during the update loop.
    *
    * sf::Vector2f position - The game world position where the object will be placed
    * sf::Vector2f size     - The size of the game object in pixels
    * return                - Pointer to the created game object
    */
    GameObject* createGameObject( std::string name, sf::Vector2f position, sf::Vector2f size );

    /**
    * Returns a pointer to the physics world
    */
    b2World* getPhysicsWorld()
    {
        return &mPhysics;
    }

    const Map* getMap() const
    {
        return &mMap;
    }

    ResourceHolder<sf::Texture, std::string>* getTextureHolder()
    {
        return &mTextures;
    }


private:

    void createEnemies();

    /**
    * ResourceHolder for textures
    */
    ResourceHolder<sf::Texture, std::string> mTextures;

    /**
    * Holds all the grids (layers) of the map in form of game objects
    */
    std::vector<std::unique_ptr<Grid>> mGrids;

    /**
    * Holds all the dynamic (non-grid) game objects
    */
    std::vector<std::unique_ptr<GameObject>> mObjects;

    /**
    * Holds all the objects that need to be created
    */
    std::vector<std::unique_ptr<GameObject>> mObjectsToCreate;

    /**
    * Holds the physical representation of the world
    */
    b2World mPhysics;

    /**
    * Holds the camera object
    */
    Camera mCamera;

    /**
    * Holds a pointer to the player object
    */
    GameObject* mPlayer;

    /**
    * Holds a pointer to the currently active map
    * Only needed as long as more than one map is cached
    */
    Map mMap;

    /**
    * Holds a pointer to the world grid, which is the only one with actual collision
    */
    Grid* mWorldGrid;

    /**
    * Customized contact listener to accomodate for the IContactable interface
    */
    PhysicsContactListener mListener;

    GameObjectFactory mGameObjectFactory;
};

#endif
