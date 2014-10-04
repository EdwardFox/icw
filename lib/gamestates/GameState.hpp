#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <SFML/Window/Event.hpp>
#include "lib/Game.hpp"

class GameState
{
public:
    virtual void init() = 0;

    virtual void cleanup() = 0;

    virtual void pause() = 0;

    virtual void resume() = 0;

    virtual void update( Game* game, sf::Vector2u windowSize, sf::Time dt ) = 0;

    virtual void render( Game* game, sf::RenderTarget& target, sf::Time dt ) = 0;

    virtual void processEvents( Game* game, const sf::Event* event ) = 0;

    virtual bool isAlwaysDrawn() const = 0;

    void changeState( Game* game, GameState* state )
    {
        game->changeState( state );
    }

protected:
    GameState()
    {
    };
};

#endif