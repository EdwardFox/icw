#include "lib/interfaces/IPhysicsComponent.hpp"
#include "lib/components/ProjectileAIComponent.hpp"
#include "lib/GameObject.hpp"

ProjectileAIComponent::ProjectileAIComponent( GameObject* gameObject ) :
        mVelocity( 0.f, 0.f )
        , mGameObject( gameObject )
{
    this->setType( "ProjectileAIComponent" );
}

void ProjectileAIComponent::update( GameObject* object, sf::Time dt )
{
    IPhysicsComponent* physComp = dynamic_cast<IPhysicsComponent*>(object->getComponent( "PhysicsComponent" ) );
    if( physComp )
    {
        if ( physComp->getBodyType() != b2_staticBody )
        {
            physComp->setLinearVelocity( b2Vec2( mVelocity.x, mVelocity.y ) );
        }
    }
}

sf::Vector2f ProjectileAIComponent::getVelocity() const
{
    return mVelocity;
}

void ProjectileAIComponent::setVelocity( sf::Vector2f velocity )
{
    mVelocity = velocity;
}

GameObject* ProjectileAIComponent::getGameObject() const
{
    return mGameObject;
}
