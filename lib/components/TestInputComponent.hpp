#ifndef TEST_INPUT_COMPONENT_HPP
#define TEST_INPUT_COMPONENT_HPP

#include "lib/interfaces/IComponent.hpp"

class TestInputComponent : public IComponent
{
    public:
        TestInputComponent();

        virtual void update(GameObject& object, sf::Time dt);
};

#endif
