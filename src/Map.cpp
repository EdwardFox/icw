#include <fstream>
#include <sstream>
#include <iostream>
#include <string.h>
#include "lib/Map.hpp"
#include "lib/rapidxml/rapidxml.hpp"

Map::Map() :
        mTiles()
        , mLayers()
        , mGroups()
        , mMapSize()
        , mTileSize()
{

}

void Map::load( std::string map, ResourceHolder<sf::Texture, std::string>& textures )
{
    /**
    * TODO: Add more safety checks
    * TODO: Make sure all properties from the XML are account for
    */

    // Load document
    rapidxml::xml_document<> doc;
    std::ifstream file( map );
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    std::string content( buffer.str() );
    if ( content != "" )
    {
        std::cout << "Successfully loaded map: " << map << std::endl << std::endl;
        std::cout << "--- --- --- --- ---" << std::endl;
    }
    else
    {
        std::cout << "Failed to load: " << map << std::endl;
    }
    doc.parse<0>( &content[0] );



    // General map data
    rapidxml::xml_node<>* rootMap = doc.first_node();
    rapidxml::xml_attribute<>* version = rootMap->first_attribute();
    rapidxml::xml_attribute<>* orientation = version->next_attribute();
    rapidxml::xml_attribute<>* width = orientation->next_attribute();
    rapidxml::xml_attribute<>* height = width->next_attribute();
    rapidxml::xml_attribute<>* tilewidth = height->next_attribute();
    rapidxml::xml_attribute<>* tileheight = tilewidth->next_attribute();

    this->mMapSize = sf::Vector2i( atoi( width->value() ), atoi( height->value() ) );
    this->mTileSize = sf::Vector2i( atoi( tilewidth->value() ), atoi( tileheight->value() ) );

    std::cout << "Map size is " << this->mMapSize.x << "x" << this->mMapSize.y << " tiles" << std::endl;
    std::cout << "Tile size is " << this->mTileSize.x << "x" << this->mMapSize.y << " pixels" << std::endl << std::endl;
    std::cout << "--- --- --- --- ---" << std::endl;


    // Tiles (of tilesets)
    rapidxml::xml_node<>* node;
    for ( node = rootMap->first_node( "tileset" ); node; node = node->next_sibling( "tileset" ) )
    {
        rapidxml::xml_attribute<>* name = node->first_attribute()->next_attribute();
        std::cout << "Parsing tileset " << name->value() << " ..." << std::endl;

        // Image data
        rapidxml::xml_node<>* image = node->first_node();
        rapidxml::xml_attribute<>* path = image->first_attribute();
        rapidxml::xml_attribute<>* imgWidth = path->next_attribute();
        rapidxml::xml_attribute<>* imgHeight = imgWidth->next_attribute();

        // Load image into resourceholder
        std::vector<std::string> parts = explode( path->value(), '/' );
        std::string texturePath = "media/textures/";
        texturePath.append( parts.back() );
        textures.load( parts.back(), texturePath );

        std::cout << "Added texture " << texturePath << " with key " << parts.back() << std::endl;

        int rows = atoi( imgHeight->value() ) / atoi( tileheight->value() );
        int columns = atoi( imgWidth->value() ) / atoi( tilewidth->value() );

        for ( int i = 0; i < rows; i++ )
        {
            for ( int j = 0; j < columns; j++ )
            {
                Tile tile;
                tile.key = parts.back();
                tile.rect = sf::IntRect(
                        j * atoi( tilewidth->value() ),
                        i * atoi( tilewidth->value() ),
                        atoi( tilewidth->value() ),
                        atoi( tileheight->value() ) );
                mTiles.push_back( tile );

                std::cout << "Added tile with key: " << tile.key << ", x: " << tile.rect.left << ", y: "
                        << tile.rect.top << ", width: " << tile.rect.width << ", height: " << tile.rect.height << std::endl;
            }
        }
        std::cout << std::endl;
    }
    std::cout << "--- --- --- --- ---" << std::endl;


    // Layer
    for ( node = rootMap->first_node( "layer" ); node; node = node->next_sibling( "layer" ) )
    {
        rapidxml::xml_attribute<>* name = node->first_attribute();
        rapidxml::xml_attribute<>* columns = name->next_attribute();
        rapidxml::xml_attribute<>* rows = columns->next_attribute();

        Layer layer;
        layer.name = name->value();
        layer.columns = atoi( columns->value() );
        layer.rows = atoi( rows->value() );

        std::cout << "Parsing layer " << layer.name << std::endl;

        int gidCount = 0;
        for ( rapidxml::xml_node<>* tile = node->first_node()->first_node(); tile; tile = tile->next_sibling() )
        {
            layer.gids.push_back( atoi( tile->first_attribute()->value() ) );
            ++gidCount;
        }
        std::cout << "Added " << gidCount << "gids to layer " << layer.name << std::endl << std::endl;

        mLayers.push_back( layer );
    }
    std::cout << "--- --- --- --- ---" << std::endl;


    // ObjectGroups
    for ( node = rootMap->first_node( "objectgroup" ); node; node = node->next_sibling( "objectgroup" ) )
    {
        ObjectGroup objGroup;
        objGroup.name = node->first_attribute()->value();
        std::cout << "Parsing ObjectGroup " << objGroup.name << " ..." << std::endl;

        rapidxml::xml_node<>* object;
        for ( object = node->first_node(); object; object = object->next_sibling() )
        {
            sf::IntRect rect(
                    atoi( object->first_attribute()->value() ),
                    atoi( object->first_attribute()->next_attribute()->value() ),
                    atoi( object->first_attribute()->next_attribute()->next_attribute()->value() ),
                    atoi( object->first_attribute()->next_attribute()->next_attribute()->next_attribute()->value() )
            );

            objGroup.objects.push_back( rect );
            std::cout << "Added object with x: " << rect.left << ", y: " << rect.top << ", width: " << rect.width
                    << ", height: " << rect.height << std::endl;
        }
        std::cout << std::endl;

        mGroups.push_back( objGroup );
    }
    std::cout << "... done" << std::endl;

}

std::vector<Map::Tile> Map::getTiles() const
{
    return mTiles;
}

std::vector<Map::Layer> Map::getLayers() const
{
    return mLayers;
}

std::vector<Map::ObjectGroup> Map::getObjectGroups() const
{
    return mGroups;
}

sf::Vector2i Map::getMapSize() const
{
    return mMapSize;
}

sf::Vector2i Map::getTileSize() const
{
    return mTileSize;
}

std::vector<std::string> Map::explode( const std::string& str, const char& ch ) const
{
    std::string next;
    std::vector<std::string> result;

    // For each character in the string
    for ( std::string::const_iterator it = str.begin(); it != str.end(); it++ )
    {
        // If we've hit the terminal character
        if ( *it == ch )
        {
            // If we have some characters accumulated
            if ( !next.empty() )
            {
                // Add them to the result vector
                result.push_back( next );
                next.clear();
            }
        }
        else
        {
            // Accumulate the next character into the sequence
            next += *it;
        }
    }
    if ( !next.empty() )
        result.push_back( next );
    return result;
}
