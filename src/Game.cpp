#include "lib/Game.hpp"
#include <lib/gamestates/StartState.hpp>

Game::Game( sf::Vector2i size, std::string title ) :
        mWindow( sf::VideoMode( size.x, size.y, 32 ), title )
        , mTimePerFrame( sf::seconds( 1.f / UPDATES_PER_SECOND ) )
        , mStates()
{
    this->changeState( new StartState( this ) );
}

void Game::processEvents()
{
    sf::Event event;
    while ( mWindow.pollEvent( event ) )
    {
        if ( event.type == sf::Event::Closed )
            mWindow.close();

        mStates.back()->processEvents( this, &event );
    }
}

void Game::render( sf::Time dt )
{
    mWindow.clear( sf::Color( 0, 100, 150 ) );

    /**
    * There are states we always want to draw, even while
    * they are not on top of the stack (e.g. game with
    * overlaying menu).
    */
    for ( const auto& val : mStates )
    {
        if ( val->isAlwaysDrawn() )
        {
            val->render( this, mWindow, dt );
        }
    }

    /** Draw stack at the top of the stack **/
    mStates.back()->render( this, mWindow, dt );

    mWindow.display();
}

void Game::update( sf::Time dt )
{
    mStates.back()->update( this, mWindow.getSize(), dt );
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

void Game::changeState( GameState* state )
{
    if ( !mStates.empty() )
    {
        mStates.back()->cleanup();
        mStates.pop_back();
    }

    mStates.push_back( std::unique_ptr<GameState>( state ) );
    mStates.back()->init();
}

void Game::pushState( GameState* state )
{
    if ( !mStates.empty() )
    {
        mStates.back()->pause();
    }

    mStates.push_back( std::unique_ptr<GameState>( state ) );
    mStates.back()->init();
}

void Game::popState()
{
    if ( !mStates.empty() )
    {
        mStates.back()->cleanup();
        mStates.pop_back();
    }

    if ( !mStates.empty() )
    {
        mStates.back()->resume();
    }
}

void Game::quit()
{
    mWindow.close();
}
