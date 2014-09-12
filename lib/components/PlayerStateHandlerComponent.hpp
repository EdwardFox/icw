#ifndef PLAYER_STATE_HANDLER_COMPONENT_HPP
#define PLAYER_STATE_HANDLER_COMPONENT_HPP

#include "lib/interfaces/IComponent.hpp"
#include "lib/interfaces/IStateHandlerComponent.hpp"

class PlayerStateHandlerComponent : public IComponent, public IStateHandlerComponent
{
public:
    PlayerStateHandlerComponent();

    virtual void update( GameObject& object, sf::Time dt );
};

#endif
