#include <fstream>
#include <sstream>
#include <iostream>
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
    * TODO: Make sure all properties from the XML are accounted for
    * TODO: Split the load function into smaller sub-functions for better maintainability
    */

    /** Load document **/
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



    /** Get root node **/
    rapidxml::xml_node<>* rootMap = doc.first_node( "map" );

    /** Root attributes **/
//    rapidxml::xml_attribute<>* version = rootMap->first_attribute( "version" );
//    rapidxml::xml_attribute<>* orientation = rootMap->first_attribute( "orientation" );
    rapidxml::xml_attribute<>* width = rootMap->first_attribute( "width" );
    rapidxml::xml_attribute<>* height = rootMap->first_attribute( "height" );
    rapidxml::xml_attribute<>* tilewidth = rootMap->first_attribute( "tilewidth" );
    rapidxml::xml_attribute<>* tileheight = rootMap->first_attribute( "tileheight" );

    /** Set map & tile size **/
    this->mMapSize = sf::Vector2i( atoi( width->value() ), atoi( height->value() ) );
    this->mTileSize = sf::Vector2i( atoi( tilewidth->value() ), atoi( tileheight->value() ) );

    std::cout << "Map size is " << this->mMapSize.x << "x" << this->mMapSize.y << " tiles" << std::endl;
    std::cout << "Tile size is " << this->mTileSize.x << "x" << this->mTileSize.y << " pixels" << std::endl << std::endl;
    std::cout << "--- --- --- --- ---" << std::endl;


    /** Parse tiles (of tilesets) **/
    rapidxml::xml_node<>* node;
    for ( node = rootMap->first_node( "tileset" ); node; node = node->next_sibling( "tileset" ) )
    {
        /** Tileset name **/
        rapidxml::xml_attribute<>* name = node->first_attribute( "name" );
        std::cout << "Parsing tileset " << name->value() << " ..." << std::endl;

        /** Image data **/
        rapidxml::xml_node<>* image = node->first_node( "image" );
        rapidxml::xml_attribute<>* path = image->first_attribute( "source" );
        rapidxml::xml_attribute<>* imgWidth = image->first_attribute( "width" );
        rapidxml::xml_attribute<>* imgHeight = image->first_attribute( "height" );

        /** Load image into resourceholder **/
        std::vector<std::string> parts = explode( path->value(), '/' );
        std::string texturePath = "media/textures/";
        texturePath.append( parts.back() );
        textures.load( parts.back(), texturePath );
        std::cout << "Added texture " << texturePath << " with key " << parts.back() << std::endl;

        /** Calculate number of rows & columns **/
        int rows = atoi( imgHeight->value() ) / atoi( tileheight->value() );
        int columns = atoi( imgWidth->value() ) / atoi( tilewidth->value() );

        /** Parse all tiles of the tileset and add it to the vector **/
        for ( int i = 0; i < rows; i++ )
        {
            for ( int j = 0; j < columns; j++ )
            {
                /** Create and fill Tile with data **/
                Tile tile;
                tile.key = parts.back();
                tile.rect = sf::IntRect(
                        j * atoi( tilewidth->value() ),
                        i * atoi( tilewidth->value() ),
                        atoi( tilewidth->value() ),
                        atoi( tileheight->value() ) );
                mTiles.push_back( tile );

//                std::cout << "Added tile with key: " << tile.key << ", x: " << tile.rect.left << ", y: "
//                        << tile.rect.top << ", width: " << tile.rect.width << ", height: " << tile.rect.height << std::endl;
            }
        }
        std::cout << std::endl;
    }
    std::cout << "--- --- --- --- ---" << std::endl;


    /** Parse Layers **/
    for ( node = rootMap->first_node( "layer" ); node; node = node->next_sibling( "layer" ) )
    {
        /** Layer attributes **/
        rapidxml::xml_attribute<>* name = node->first_attribute( "name" );
        rapidxml::xml_attribute<>* columns = node->first_attribute( "width" );
        rapidxml::xml_attribute<>* rows = node->first_attribute( "height" );

        Layer layer;
        layer.name = name->value();
        layer.columns = atoi( columns->value() );
        layer.rows = atoi( rows->value() );

        std::cout << "Parsing layer " << layer.name << std::endl;

        /** Add all tile gids to the layer **/
        int gidCount = 0;
        for ( rapidxml::xml_node<>* tile = node->first_node( "data" )->first_node( "tile" ); tile; tile = tile->next_sibling( "tile" ) )
        {
            layer.gids.push_back( atoi( tile->first_attribute( "gid" )->value() ) );
            ++gidCount;
        }
        std::cout << "Added " << gidCount << "gids to layer " << layer.name << std::endl << std::endl;

        /** Add layer to the layers vector **/
        mLayers.push_back( layer );
    }
    std::cout << "--- --- --- --- ---" << std::endl;


    /** ObjectGroups **/
    for ( node = rootMap->first_node( "objectgroup" ); node; node = node->next_sibling( "objectgroup" ) )
    {
        /** Get ObjectGroup Name **/
        ObjectGroup objGroup;
        objGroup.name = node->first_attribute( "name" )->value();
        std::cout << "Parsing ObjectGroup " << objGroup.name << " ..." << std::endl;

        /** Parse all objects in the objectgroup **/
        for ( rapidxml::xml_node<>* object = node->first_node( "object" ); object; object = object->next_sibling( "object" ) )
        {
            sf::IntRect rect(
                    atoi( object->first_attribute( "x" )->value() ),
                    atoi( object->first_attribute( "y" )->value() ),
                    (object->first_attribute( "width" )) ? atoi( object->first_attribute( "width" )->value() ) : 0,
                    (object->first_attribute( "height" )) ? atoi( object->first_attribute( "height" )->value() ) : 0
            );

            MapObject mapObject;
            mapObject.position = rect;

            if ( object->first_attribute( "name" ) )
            {
                mapObject.name = object->first_attribute( "name" )->value();
            }

            if ( object->first_attribute( "type" ) )
            {
                mapObject.type = object->first_attribute( "type" )->value();
            }

            rapidxml::xml_node<>* properties = object->first_node( "properties" );
            if ( properties )
            {
                for ( rapidxml::xml_node<>* property = properties->first_node( "property" ); property; property = property->next_sibling( "property" ) )
                {
                    std::tuple<std::string, std::string> propertyTupel( property->first_attribute( "name" )->value(), property->first_attribute( "value" )->value() );
                    mapObject.properties.push_back( propertyTupel );
                }
            }

            objGroup.objects.push_back( mapObject );
            std::cout << "Added object with x: " << rect.left << ", y: " << rect.top << ", width: " << rect.width
                    << ", height: " << rect.height << std::endl;
        }
        std::cout << std::endl;

        mGroups.emplace( node->first_attribute( "name" )->value(), objGroup );
    }
    std::cout << "... done" << std::endl;

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
