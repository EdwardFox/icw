#include <lib/gamestates/StartState.hpp>
#include "lib/gamestates/PlayState.hpp"

PlayState::PlayState( std::string map ) :
        mWorld()
        , mDrawAlways( true )
        , mMap( map )
{

}

void PlayState::init()
{
    mWorld.loadMap( mMap );

    Map map = *mWorld.getMap();

    /**
    * Set up the camera
    */
    Camera camera;
    camera.setOffset( sf::Vector2f( 0.f, -50.f ) );
    camera.setZoom( 3.f );
    camera.setFollowTarget( mWorld.getPlayer(), true );
    camera.setLagBehindAmount( 0.2f );
    sf::IntRect rect( 0, 0, map.getMapSize().x * map.getTileSize().x, map.getMapSize().y * map.getTileSize().x );
    camera.setBorders( rect );

    mWorld.setCamera( camera );
}

void PlayState::cleanup()
{
}

void PlayState::pause()
{

}

void PlayState::resume()
{

}

void PlayState::update( Game* game, sf::Vector2u windowSize, sf::Time dt )
{
    mWorld.update( dt, windowSize );
}

void PlayState::render( Game* game, sf::RenderTarget& target, sf::Time dt )
{
    mWorld.render( target, dt );
}

void PlayState::processEvents( Game* game, const sf::Event* event )
{
    if( event->key.code == sf::Keyboard::Escape )
    {
        game->changeState( new StartState( game ) );
    }
}

bool PlayState::isAlwaysDrawn() const
{
    return mDrawAlways;
}

void PlayState::changeState( Game* game, GameState* state )
{
    game->changeState( state );
}
