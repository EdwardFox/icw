#ifndef GAME_HPP
#define GAME_HPP

#include <string>
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

private:
    sf::RenderWindow mWindow;
    sf::Time mTimePerFrame;
    std::vector<GameState*> mStates;
};

#endif
