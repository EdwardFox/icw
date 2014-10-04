#include "lib/gamestates/PlayState.hpp"

/** Make our static members known **/
PlayState PlayState::mPlayState;
World PlayState::mWorld;
bool PlayState::mDrawAlways;

void PlayState::init()
{
    mDrawAlways = true;
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

}

bool PlayState::isAlwaysDrawn() const
{
    return mDrawAlways;
}
