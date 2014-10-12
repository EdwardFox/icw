#include <lib/gamestates/PlayState.hpp>
#include <lib/Game.hpp>
#include <lib/menu/TextButton.hpp>
#include "lib/gamestates/StartState.hpp"

StartState::StartState( Game* game ) :
        mDrawAlways( false )
        , mWorld()
        , mMenu()
        , mOffset()
        , mGame( game )
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

    sf::Vector2f windowSize( mGame->getTarget()->getSize().x / camera.getZoom(), mGame->getTarget()->getSize().y / camera.getZoom() );

    TextButton* play = new TextButton();
    play->setFont( "media/fonts/Arial.ttf" );
    play->setText( "Play" );
    play->setTextColor( sf::Color::White );
    play->setHighlightTextColor( sf::Color::Green );
    play->setPosition( sf::Vector2f( 40.f, 40.f ) );
    play->setOffset( mOffset );
    play->setZoom( camera.getZoom() );
    play->setSize( sf::Vector2f( 80.f, 20.f ) );
    play->setBackgroundColor( sf::Color( 0.f, 0.f, 0.f, 200.f ) );
    play->setVisible( true );
    play->setClickFunction( [] ( Menu* menu, Game* game )
    {
        game->changeState( new PlayState( "media/maps/Temple.tmx" ) );
    });
    mMenu.addItem( "Play", play );

    TextButton* quit = new TextButton();
    quit->setFont( "media/fonts/Arial.ttf" );
    quit->setText( "Quit" );
    quit->setTextColor( sf::Color::White );
    quit->setHighlightTextColor( sf::Color::Green );
    quit->setPosition( sf::Vector2f( 40.f, windowSize.y - 60.f ) );
    quit->setOffset( mOffset );
    quit->setZoom( camera.getZoom() );
    quit->setSize( sf::Vector2f( 80.f, 20.f ) );
    quit->setBackgroundColor( sf::Color( 0.f, 0.f, 0.f, 200.f ) );
    quit->setVisible( true );
    quit->setClickFunction( [] ( Menu* menu, Game* game )
    {
        game->quit();
    });
    mMenu.addItem( "Quit", quit );
}

void StartState::cleanup()
{
    mMenu.clear();
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

    sf::RectangleShape rect;
    rect.setSize( sf::Vector2f(target.getSize().x, target.getSize().y) );
    rect.setFillColor( sf::Color( 0.f, 0.f, 0.f, 100.f) );
    target.draw(rect);

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
