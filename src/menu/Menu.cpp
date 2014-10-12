#include <lib/Game.hpp>
#include "lib/menu/Menu.hpp"

Menu::Menu() :
        mOffset()
        , mItems()
        , mZoom()
{

}

void Menu::update( sf::Vector2u windowSize, sf::Time dt )
{
    for ( const auto& item : mItems )
    {
        if ( item.second->isVisible() )
            item.second->update( windowSize, dt );
    }
}

void Menu::render( sf::RenderTarget& target, sf::Time dt ) const
{
    for ( const auto& item : mItems )
    {
        if ( item.second->isVisible() )
            item.second->render( target, dt );
    }
}

void Menu::processEvents( Game* game, const sf::Event* event )
{
    if ( event->type == sf::Event::MouseButtonPressed )
    {
        if ( event->mouseButton.button == sf::Mouse::Left )
        {
            float x = event->mouseButton.x / mZoom;
            float y = event->mouseButton.y / mZoom;

            for ( const auto& item : mItems )
            {
                sf::FloatRect rect;
                rect.left = item.second->getPosition().x;
                rect.top = item.second->getPosition().y;
                rect.width = item.second->getSize().x;
                rect.height = item.second->getSize().y;

                std::cout << "[AREA] x: " << rect.left << ", y: " << rect.top << ", width: " << rect.width << ", height: " << rect.height << std::endl;
                std::cout << "[MOUSE] x: " << x << ", y: " << y << std::endl;

                if ( rect.contains( x, y ) && item.second->isVisible() )
                {
                    item.second->onClick( this, game );
                }
            }
        }
    }
}
