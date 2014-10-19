#include <lib/Game.hpp>
#include "lib/menu/Menu.hpp"

Menu::Menu() :
        mItems()
{

}

void Menu::update( sf::Vector2u windowSize, sf::Time dt )
{
    for ( const auto& item : mItems )
    {
        if ( item.second->isVisible() )
        {
            item.second->update( windowSize, dt );
        }
    }
}

void Menu::render( sf::RenderTarget& target, sf::Time dt ) const
{
    for ( const auto& item : mItems )
    {
        if ( item.second->isVisible() )
        {
            item.second->render( target, dt );
        }
    }
}

void Menu::processEvents( Game* game, const sf::Event* event )
{

    if ( event->type == sf::Event::MouseButtonPressed )
    {
        if ( event->mouseButton.button == sf::Mouse::Left )
        {
            for ( const auto& item : mItems )
            {
                sf::FloatRect rect;
                rect.left = item.second->getPosition().x;
                rect.top = item.second->getPosition().y;
                rect.width = item.second->getSize().x;
                rect.height = item.second->getSize().y;
                float x = event->mouseButton.x;
                float y = event->mouseButton.y;


                if ( rect.contains( x, y ) && item.second->isVisible() )
                {
                    if( item.second->onClick( this, game ) )
                        break;
                }
            }
        }
    }

    if ( event->type == sf::Event::MouseMoved )
    {
        for ( const auto& item : mItems )
        {
            sf::FloatRect rect;
            rect.left = item.second->getPosition().x;
            rect.top = item.second->getPosition().y;
            rect.width = item.second->getSize().x;
            rect.height = item.second->getSize().y;

            float x = event->mouseMove.x;
            float y = event->mouseMove.y;

            if ( rect.contains( x, y ) && item.second->isVisible() )
            {
                item.second->onHover( this, true );
            }
            else
            {
                item.second->onHover( this, false );
            }
        }
    }
}