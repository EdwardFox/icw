#include <lib/gamestates/PlayState.hpp>
#include <lib/Game.hpp>
#include <lib/menu/TextButton.hpp>
#include "lib/gamestates/StartState.hpp"

StartState::StartState() :
        mDrawAlways( false )
        , mWorld()
        , mMenu()
        , mOffset()
{

}

void StartState::init()
{
    mWorld.loadMap( "media/maps/Screen.tmx" );

    /**
    * Set up the camera
    */
    mOffset.x = mWorld.getGameObjectById( 0 )->getPosition().x - 100.f;
    mOffset.y = mWorld.getGameObjectById( 0 )->getPosition().y + - 50.f;

    Camera camera;
    camera.setPosition( sf::Vector2f( mOffset.x, mOffset.y ) );
    camera.setZoom( 3.f );

    mWorld.setCamera( camera );

    mMenu.setOffset( mOffset );
    mMenu.setZoom( camera.getZoom() );

    sf::Font font;
    font.loadFromFile( "media/fonts/Arial.ttf" );

    sf::Text text;
    text.setString( "Play" );
//    text.setScale( 0.5f, 0.5f );
    text.setColor( sf::Color::White );

    TextButton* play = new TextButton();
    play->setFont( font );
    play->setText( text );
    play->setPosition( sf::Vector2f( 0.f, 0.f ) );
    play->setOffset( mOffset );
    play->setZoom( camera.getZoom() );
    play->setSize( sf::Vector2f( 200.f, 50.f ) );
    play->setBackgroundColor( sf::Color( 100.f, 100.f, 100.f ) );
    play->setVisible( true );
    play->setClickFunction( [] ( Menu* menu, Game* game )
    {
        game->changeState( new PlayState( "media/maps/Temple.tmx" ) );
    });

    mMenu.addItem( "Play", play );
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
    mWorld.update( dt, windowSize );

    mMenu.update( windowSize, dt );
}

void StartState::render( Game* game, sf::RenderTarget& target, sf::Time dt )
{
    mWorld.render( target, dt );


    mMenu.render( target, dt );
}

void StartState::processEvents( Game* game, const sf::Event* event )
{
    if ( event->key.code == sf::Keyboard::Escape )
    {
//        game->quit();
    }

    if ( event->key.code == sf::Keyboard::Return )
    {
//        game->changeState( new PlayState( "media/maps/Temple.tmx" ) );
    }

    mMenu.processEvents( game, event );
}

bool StartState::isAlwaysDrawn() const
{
    return mDrawAlways;
}

void StartState::changeState( Game* game, GameState* state )
{
    game->changeState( state );
}
