#include "lib/interfaces/IPhysicsComponent.hpp"
#include "lib/components/TestAIComponent.hpp"
#include "lib/GameObject.hpp"

TestAIComponent::TestAIComponent() :
        mThreshold( 50.f )
        , mCurrent( 0.f )
        , mIncreaser( 1.f )
{
    this->setType( "InputComponent" );
}

void TestAIComponent::update( GameObject& object, sf::Time dt )
{
    IPhysicsComponent* physComp = dynamic_cast<IPhysicsComponent*>(object.getComponent( "PhysicsComponent" ) );
    if( physComp )
    {
        if ( physComp->getBodyType() != b2_staticBody )
        {
            physComp->setLinearVelocity( b2Vec2( 0.f, -0.5f ) );

        }
    }
}
