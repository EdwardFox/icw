#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include "lib/gamestates/GameState.hpp"
#include "lib/World.hpp"

class GameState;

class Game
{
public:
    Game( sf::Vector2i size, std::string title );

    void processEvents();

    void render( sf::Time dt );

    void update( sf::Time dt );

    void run();

    void changeState( GameState* state );

    void pushState( GameState* state );

    void popState();

    void quit();

    const sf::RenderTarget* getTarget() const
    {
        return &mWindow;
    }

private:
    sf::RenderWindow mWindow;
    sf::Time mTimePerFrame;
    std::vector<std::unique_ptr<GameState>> mStates;
};

#endif
