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
        , mButtonSize( 200.f, 60.f )
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

    sf::Vector2f windowSize( mGame->getTarget()->getSize().x, mGame->getTarget()->getSize().y );

    TextButton* play = new TextButton();
    play->setFont( DEFAULT_FONT);
    play->setText( "Play" );
    play->setTextColor( sf::Color::White );
    play->setHighlightTextColor( sf::Color::Green );
    play->setPosition( sf::Vector2f( 100.f, windowSize.y - 240.f ) );
    play->setSize( mButtonSize );
    play->setBackgroundColor( sf::Color( 0.f, 0.f, 0.f, 200.f ) );
    play->setVisible( true );
    play->setClickFunction( [] ( Menu* menu, Game* game )
    {
        game->pushState( new PlayState( "media/maps/Temple.tmx" ) );
    });
    mMenu.addItem( "1_Play", play );

    TextButton* quit = new TextButton();
    quit->setFont( DEFAULT_FONT );
    quit->setText( "Quit" );
    quit->setTextColor( sf::Color::White );
    quit->setHighlightTextColor( sf::Color::Green );
    quit->setPosition( sf::Vector2f( 100.f, windowSize.y - 160.f ) );
    quit->setSize( mButtonSize );
    quit->setBackgroundColor( sf::Color( 0.f, 0.f, 0.f, 200.f ) );
    quit->setVisible( true );
    quit->setClickFunction( [] ( Menu* menu, Game* game )
    {
        game->quit();
    });
    mMenu.addItem( "2_Quit", quit );
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
    mWorld.update( dt, windowSize, game );

    mMenu.update( windowSize, dt );
}

void StartState::render( Game* game, sf::RenderTarget& target, sf::Time dt )
{
    mWorld.render( target, dt );

    target.setView( target.getDefaultView() );

    sf::RectangleShape rect;
    rect.setSize( sf::Vector2f(target.getSize().x, target.getSize().y) );
    rect.setFillColor( sf::Color( 0.f, 0.f, 0.f, 100.f) );
    target.draw(rect);

    mMenu.render( target, dt );
}

bool StartState::processEvents( Game* game, const sf::Event* event )
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

    return false;
}

bool StartState::isAlwaysDrawn() const
{
    return mDrawAlways;
}

void StartState::changeState( Game* game, GameState* state )
{
    game->changeState( state );
}
