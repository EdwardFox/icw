#include "lib/components/TestAIComponent.hpp"
#include "lib/GameObject.hpp"

TestAIComponent::TestAIComponent() :
mThreshold(50.f)
, mCurrent(0.f)
, mIncreaser(1.f)
{
    this->setType("TestAIComponent");
}

void TestAIComponent::update(GameObject& object, sf::Time dt)
{
    if(mCurrent > mThreshold || mCurrent < -mThreshold)
        mIncreaser = -mIncreaser;

    sf::Vector2f pos = object.getPosition();
    pos.y += mIncreaser;
    mCurrent += mIncreaser;
    object.setPosition(pos);
}
