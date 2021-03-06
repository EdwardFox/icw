#ifndef MAP_LOADER_HPP
#define MAP_LOADER_HPP

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include <vector>
#include "lib/ResourceHolder.hpp"
#include <tuple>

/**
* Parses Tiled map objects in the XML format and saves relevant data
* for further processing
*/
class Map
{
public:

    /**
    * Holds all relevant data to identify each tile of a tileset
    */
    struct Tile
    {
        /**
        * Holds the key to the texture resource
        */
        std::string key;

        /**
        * Defines the section of the texture to be displayed
        */
        sf::IntRect rect;
    };

    /**
    * Holds all relevant data to create a layer
    */
    struct Layer
    {
        /**
        * The layer name
        */
        std::string name;

        /**
        * The amount of rows
        */
        int rows;

        /**
        * The amount of columns
        */
        int columns;

        /**
        * Saves all gids from each tile in sequential order
        */
        std::vector<int> gids;
    };

    /**
    * Holds single map objects
    */
    struct MapObject
    {
        /**
        * The objects name
        */
        std::string name;

        /**
        * The objects type
        */
        std::string type;

        /**
        * Position and dimensions
        */
        sf::IntRect position;

        /**
        * Each object is saved as an MapObject struct
        */
        std::vector<std::tuple<std::string,std::string>> properties;
    };

    /**
    * Holds all relevant data for ObjectGroups
    */
    struct ObjectGroup
    {
        /**
        * The ObjectGroups name
        */
        std::string name;

        /**
        * Each object is saved as an IntRect, containing its position and size in the world
        */
        std::vector<MapObject> objects;
    };

    /**
    * Initializes all variables
    */
    Map();

    /**
    * Loads and parses the Tiled map and adds the used textures to the texture resourceholder
    *
    * std::string map                                       - The path of the tmx file to load
    * ResourceHolder<sf::Texture, std::string>& textures    - Reference to the texture resourceholder
    */
    void load( std::string map, ResourceHolder<sf::Texture, std::string>& textures );

    /**
    * Returns the vector that holds the different tile data for each tileset
    */
    const std::vector<Map::Tile>* getTiles() const
    {
        return &mTiles;
    }

    /**
    * Returns the vector that holds the different layers
    */
    const std::vector<Map::Layer>* getLayers()
    {
        return &mLayers;
    }

    /**
    * Returns the vector that holds the different objectgroups
    */
    const std::unordered_map<std::string, Map::ObjectGroup>* getObjectGroups() const
    {
        return &mGroups;
    }

    /**
    * Returns the map size
    */
    sf::Vector2i getMapSize() const
    {
        return mMapSize;
    }

    /**
    * Returns the tile size
    */
    sf::Vector2i getTileSize() const
    {
        return mTileSize;
    }

private:
    /**
    * Helper function that splits a string by a delimiter
    *
    * const std::string& str    - The string to split
    * const char& ch            - The delimiter to split the string with
    * return                    - A vector containing the split string parts
    */
    std::vector<std::string> explode( const std::string& str, const char& ch ) const;

    /**
    * Contains the tileset tile definitions
    */
    std::vector<Tile> mTiles;

    /**
    * Contains the layers of the map
    */
    std::vector<Layer> mLayers;

    /**
    * Contains the object groups of the map
    */
    std::unordered_map<std::string, ObjectGroup> mGroups;

    /**
    * Contains the maps size
    */
    sf::Vector2i mMapSize;

    /**
    * Contains the tile size
    */
    sf::Vector2i mTileSize;

};

#endif