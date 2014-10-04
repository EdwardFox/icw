#ifndef PLAYSTATE_HPP
#define PLAYSTATE_HPP

#include "GameState.hpp"

class PlayState : public GameState
{

public:
    virtual void init() override;

    virtual void cleanup() override;

    virtual void pause() override;

    virtual void resume() override;

    virtual void update( Game* game, sf::Vector2u windowSize, sf::Time dt ) override;

    virtual void render( Game* game, sf::RenderTarget& target, sf::Time dt ) override;

    virtual void processEvents( Game* game, const sf::Event* event ) override;

    virtual bool isAlwaysDrawn() const override;

    static PlayState* instance()
    {
        return &mPlayState;
    }

protected:
    PlayState()
    {
    };

private:
    static PlayState mPlayState;
    static World mWorld;
    static bool mDrawAlways;
};

#endif