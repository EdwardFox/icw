#ifndef MAP_LOADER_HPP
#define MAP_LOADER_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "lib/ResourceHolder.hpp"

class Map
{
public:
    struct Tile
    {
        std::string key;
        sf::IntRect rect;
    };

    struct Layer
    {
        std::string name;
        int rows;
        int columns;
        std::vector<int> gids;
    };

    struct ObjectGroup
    {
        std::string name;
        std::vector<sf::IntRect> objects;
    };

    Map();

    void load( std::string map, ResourceHolder<sf::Texture, std::string>& textures );

    std::vector<Tile> getTiles() const;

    std::vector<Layer> getLayers() const;

    std::vector<ObjectGroup> getObjectGroups() const;

    sf::Vector2i getMapSize() const;

    sf::Vector2i getTileSize() const;

private:
    std::vector<std::string> explode(const std::string& str, const char& ch) const;

    std::vector<Tile> mTiles;
    std::vector<Layer> mLayers;
    std::vector<ObjectGroup> mGroups;
    sf::Vector2i mMapSize;
    sf::Vector2i mTileSize;

};

#endif