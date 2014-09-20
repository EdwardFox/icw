#ifndef TEST_AI_COMPONENT_HPP
#define TEST_AI_COMPONENT_HPP

#include "lib/interfaces/IComponent.hpp"
#include "lib/interfaces/IInputComponent.hpp"

class TestAI2Component : public IComponent, public IInputComponent
{
    public:
        TestAI2Component();

        virtual void update(GameObject& object, sf::Time dt);
    private:
        float mThreshold;
        float mCurrent;
        float mIncreaser;
};

#endif
