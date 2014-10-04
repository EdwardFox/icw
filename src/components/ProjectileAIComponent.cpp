#include <lib/interfaces/IProjectileMovementComponent.hpp>
#include "lib/interfaces/IPhysicsComponent.hpp"
#include "lib/components/ProjectileAIComponent.hpp"

ProjectileAIComponent::ProjectileAIComponent( GameObject* gameObject ) :
        mGameObject( gameObject )
        , mTimeAlive( 0 )
        , mMaxTimeAlive( 3000 ) // Projectile may only live 3000 milliseconds
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

    /** Kill projectile if it has lived longer than its maximum lifespan **/
    if( mTimeAlive >= mMaxTimeAlive )
    {
        mGameObject->setExpired( true );
    }
    else
    {
        mTimeAlive += dt.asMilliseconds();
    }
}



