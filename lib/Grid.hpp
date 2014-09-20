#ifndef GRID_HPP
#define GRID_HPP

#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include "lib/Data.hpp"
#include "lib/GameObject.hpp"

class Camera;

class Grid
{
public:
    typedef std::unique_ptr<GameObject> entPtr;

    Grid( std::string name );

    GameObject* const getTile( std::string key ) const;

    sf::Vector2i getGridPosition( sf::Vector2f position );

    std::string getTileKeyByPosition( sf::Vector2f position );

    unsigned getTileSize() const;

    void addTile( std::string key, GameObject* ent );

    void removeTile( std::string key );

    void setTileSize( unsigned tileSize );

    void render( sf::RenderTarget& target, sf::Time dt, sf::Vector2u windowSize, const Camera* camera ) const;

    void update( sf::Time dt );

    std::string getName() const;

    void setName( std::string name );

private:

    std::string mName;
    std::map<std::string, entPtr> mGrid;
    unsigned mTileSize;
};

#endif
