#include "lib/interfaces/IPhysicsComponent.hpp"
#include "lib/components/TestAI2Component.hpp"
#include "lib/GameObject.hpp"

TestAI2Component::TestAI2Component() :
        mThreshold( 50.f )
        , mCurrent( 0.f )
        , mIncreaser( 1.f )
{
    this->setType( "InputComponent" );
}

void TestAI2Component::update( GameObject& object, sf::Time dt )
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
