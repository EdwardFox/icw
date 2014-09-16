#ifndef TEST_INPUT_COMPONENT_HPP
#define TEST_INPUT_COMPONENT_HPP

#include "lib/interfaces/IComponent.hpp"
#include "lib/interfaces/IInputComponent.hpp"
#include "lib/Data.hpp"

class PlayerInputComponent : public IComponent, public IInputComponent
{
public:
    PlayerInputComponent();

    virtual void update( GameObject& object, sf::Time dt );

private:
};

#endif
