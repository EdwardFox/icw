#ifndef PLAYER_STATE_HANDLER_COMPONENT_HPP
#define PLAYER_STATE_HANDLER_COMPONENT_HPP

#include "lib/interfaces/IComponent.hpp"
#include "lib/interfaces/IStateHandlerComponent.hpp"

class DefaultStateHandlerComponent : public IComponent, public IStateHandlerComponent
{
public:
    DefaultStateHandlerComponent();

    virtual void update( GameObject& object, sf::Time dt );
};

#endif
