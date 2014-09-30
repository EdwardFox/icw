#include <lib/interfaces/IProjectileMovementComponent.hpp>
#include "lib/interfaces/IPhysicsComponent.hpp"
#include "lib/components/ProjectileAIComponent.hpp"
#include "lib/GameObject.hpp"

ProjectileAIComponent::ProjectileAIComponent( GameObject* gameObject ) :
        mGameObject( gameObject )
{
    this->setType( "ProjectileAIComponent" );
}

void ProjectileAIComponent::update( GameObject* object, sf::Time dt )
{
    IPhysicsComponent* physComp = dynamic_cast<IPhysicsComponent*>(object->getComponent( "PhysicsComponent" ) );
    if ( physComp )
    {
        if ( physComp->getBodyType() != b2_staticBody )
        {
            IProjectileMovementComponent* moveComp = dynamic_cast<IProjectileMovementComponent*>( object->getComponent( "MovementComponent" ) );
            if( moveComp )
            {
                moveComp->move( object );
            }
        }
    }
}



