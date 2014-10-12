#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/System/Vector2.hpp>
#include <memory>
#include <string>
#include <unordered_map>
#include <SFML/Window/Event.hpp>
#include "lib/menu/Item.hpp"

class Game;

class Menu
{
public:
    Menu();

    void update( sf::Vector2u windowSize, sf::Time dt );

    void render( sf::RenderTarget& target, sf::Time dt ) const;

    void processEvents( Game* game, const sf::Event* event );

    sf::Vector2f getOffset() const
    {
        return mOffset;
    }

    void setOffset( sf::Vector2f offset )
    {
        mOffset = offset;
    }

    void addItem( std::string key, Item* item )
    {
        mItems.emplace( key, std::unique_ptr<Item>( item ) );
    }

    Item* getItemByKey( std::string key )
    {
        try
        {
            return mItems.at( key ).get();
        }
        catch( std::out_of_range oor )
        {
            return nullptr;
        }

    }

    float getZoom() const
    {
        return mZoom;
    }

    void setZoom( float zoom )
    {
        mZoom = zoom;
    }

private:
    sf::Vector2f mOffset;
    std::unordered_map<std::string, std::unique_ptr<Item>> mItems;
    float mZoom;
};

#endif