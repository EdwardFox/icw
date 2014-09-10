#include "lib/Game.hpp"

Game::Game( sf::Vector2i size, std::string title ) :
        mWindow( sf::VideoMode( size.x, size.y, 32 ), title )
        , mTimePerFrame( sf::seconds( 1.f / UPDATES_PER_SECOND ) )
        , mWorld()
{

}

void Game::processEvents()
{
    sf::Event event;
    while ( mWindow.pollEvent( event ) )
    {
        if ( event.type == sf::Event::Closed )
            mWindow.close();

        if ( event.key.code == sf::Keyboard::Escape )
            mWindow.close();
    }
}

void Game::render( sf::Time dt )
{
    mWindow.clear( sf::Color::White );
    mWorld.render( mWindow, dt );
    mWindow.display();
}

void Game::update( sf::Time dt )
{
    mWorld.update( dt );
}

void Game::run()
{
    // Update
    sf::Clock updateClock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    // Render
    sf::Clock renderClock;
    sf::Time timeSinceLastRender = sf::Time::Zero;

    while ( mWindow.isOpen() )
    {
        timeSinceLastUpdate += updateClock.restart();
        while ( timeSinceLastUpdate > mTimePerFrame )
        {
            processEvents();
            update( mTimePerFrame );
            timeSinceLastUpdate -= mTimePerFrame;
        }

        timeSinceLastRender += renderClock.restart();
        render( timeSinceLastRender );
        timeSinceLastRender = sf::Time::Zero;
    }
}
