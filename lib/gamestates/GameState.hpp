#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class Game;

class GameState
{
public:

    virtual ~GameState() {};

    virtual void init() = 0;

    virtual void cleanup() = 0;

    virtual void pause() = 0;

    virtual void resume() = 0;

    virtual void update( Game* game, sf::Vector2u windowSize, sf::Time dt ) = 0;

    virtual void render( Game* game, sf::RenderTarget& target, sf::Time dt ) = 0;

    virtual bool processEvents( Game* game, const sf::Event* event ) = 0;

    virtual bool isAlwaysDrawn() const = 0;

    virtual void changeState( Game* game, GameState* state ) = 0;

};

#endif