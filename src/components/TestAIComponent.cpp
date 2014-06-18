#include "lib/interfaces/IPhysicsComponent.hpp"
#include "lib/components/TestAIComponent.hpp"
#include "lib/GameObject.hpp"

TestAIComponent::TestAIComponent() :
mThreshold(50.f)
, mCurrent(0.f)
, mIncreaser(1.f)
{
    this->setType("InputComponent");
}

void TestAIComponent::update(GameObject& object, sf::Time dt)
{
    ComponentCommand<IPhysicsComponent&> command;
    command.targetType = "PhysicsComponent";
    command.execute = [] (IPhysicsComponent& comp) {
        if(comp.getBodyType() != b2_staticBody) {
            comp.setLinearVelocity(b2Vec2(0.f, -0.5f));
        }
    };

    object.broadcastComponentCommand(command);
}
