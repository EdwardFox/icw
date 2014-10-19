#ifndef PLAYSTATE_HPP
#define PLAYSTATE_HPP

#include "lib/gamestates/GameState.hpp"
#include "lib/World.hpp"

class PlayState : public GameState
{

public:
    PlayState( std::string map );

    virtual void init() override;

    virtual void cleanup() override;

    virtual void pause() override;

    virtual void resume() override;

    virtual void update( Game* game, sf::Vector2u windowSize, sf::Time dt ) override;

    virtual void render( Game* game, sf::RenderTarget& target, sf::Time dt ) override;

    virtual bool processEvents( Game* game, const sf::Event* event ) override;

    virtual bool isAlwaysDrawn() const override;

    virtual void changeState( Game* game, GameState* state ) override;

private:
    World mWorld;
    bool mDrawAlways;
    std::string mMap;
};

#endif