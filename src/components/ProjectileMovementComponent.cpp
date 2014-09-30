#include <lib/interfaces/IPhysicsComponent.hpp>
#include "lib/components/ProjectileMovementComponent.hpp"

ProjectileMovementComponent::ProjectileMovementComponent( GameObject* object ) :
        mGameObject( object )
        , mMovementSpeed( 0.f, 0.f )
{
    this->setType( "ProjectileMovementComponent" );
}

void ProjectileMovementComponent::update( GameObject* object, sf::Time dt )
{

}

void ProjectileMovementComponent::move( GameObject* object )
{
    IPhysicsComponent* physComp = dynamic_cast<IPhysicsComponent*>( object->getComponent( "PhysicsComponent" ) );
    if ( physComp )
    {
        physComp->setLinearVelocity( b2Vec2( mMovementSpeed.x, mMovementSpeed.y ) );
    }
}
