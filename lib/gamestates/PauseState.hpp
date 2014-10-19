#ifndef PAUSESTATE_HPP
#define PAUSESTATE_HPP

#include <lib/Game.hpp>
#include <lib/menu/Menu.hpp>
#include "GameState.hpp"

class PauseState : public GameState
{

public:
    PauseState( Game* game, std::string map );

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
    bool mDrawAlways;
    Menu mMenu;
    sf::Vector2f mOffset;
    Game* mGame;
    std::string mMap;
};

#endif