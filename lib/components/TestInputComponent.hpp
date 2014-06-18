#ifndef TEST_INPUT_COMPONENT_HPP
#define TEST_INPUT_COMPONENT_HPP

#include "lib/interfaces/IComponent.hpp"
#include "lib/interfaces/IInputComponent.hpp"

class TestInputComponent : public IComponent, public IInputComponent
{
    public:
        TestInputComponent();

        virtual void update(GameObject& object, sf::Time dt);
};

#endif
