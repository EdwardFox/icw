#ifndef TEST_AI_COMPONENT_HPP
#define TEST_AI_COMPONENT_HPP

#include "lib/interfaces/IComponent.hpp"
#include "lib/interfaces/IInputComponent.hpp"

class TestAIComponent : public IComponent, public IInputComponent
{
    public:
        TestAIComponent();

        virtual void update(GameObject& object, sf::Time dt);
    private:
        float mThreshold;
        float mCurrent;
        float mIncreaser;
};

#endif
