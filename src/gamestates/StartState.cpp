#include <lib/gamestates/PlayState.hpp>
#include "lib/gamestates/StartState.hpp"

/** Make our static members known **/
StartState StartState::mStartState;
bool StartState::mDrawAlways;

void StartState::init()
{
    mDrawAlways = false;
}

void StartState::cleanup()
{

}

void StartState::pause()
{

}

void StartState::resume()
{

}

void StartState::update( Game* game, sf::Vector2u windowSize, sf::Time dt )
{
}

void StartState::render( Game* game, sf::RenderTarget& target, sf::Time dt )
{
    sf::Vector2u windowSize = target.getSize();

    target.setView( target.getDefaultView() );

    sf::RectangleShape rect;
    rect.setSize( sf::Vector2f( windowSize.x, windowSize.y ) );
    rect.setPosition( 0.f, 0.f );
    rect.setFillColor( sf::Color::Black );
    target.draw( rect );

    sf::Font font;
    font.loadFromFile( "media/fonts/Arial.ttf" );

    sf::Text text;
    text.setString( "Press Enter to start the game" );
    text.setFont( font );
    text.setPosition( windowSize.x / 2.f - text.getLocalBounds().width / 2.f, windowSize.y / 2.f );
    text.setColor( sf::Color::White );
//    text.setScale( 2.f, 2.f );
    target.draw( text );

    sf::Texture tex;
    tex.loadFromFile( "media/textures/start.png" );
    sf::Sprite sprite;
    sprite.setTexture( tex );
    target.draw( sprite );
}

void StartState::processEvents( Game* game, const sf::Event* event )
{
    if ( event->key.code == sf::Keyboard::Escape )
    {
//        game->quit();
    }

    if ( event->key.code == sf::Keyboard::Return )
    {
        game->changeState( PlayState::instance() );
    }
}

bool StartState::isAlwaysDrawn() const
{
    return mDrawAlways;
}
