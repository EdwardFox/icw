#include <lib/components/ProjectileMovementComponent.hpp>
#include "lib/gameobjects/EnemyA.hpp"
#include "lib/components/SolidColorGraphicsComponent.hpp"
#include "lib/components/Box2DPhysicsComponent.hpp"
#include "lib/components/ProjectileAIComponent.hpp"
#include "lib/World.hpp"

EnemyA::EnemyA( World* world, std::string name, sf::Vector2f position, sf::Vector2f size ) :
        GameObject( world, name, position, size )
{
    createDefaultComponents();
}

void EnemyA::createDefaultComponents()
{
    SolidColorGraphicsComponent* solid = new SolidColorGraphicsComponent( this, this->getSize() );
    this->setGraphicComponent( solid );

    Box2DPhysicsComponent* physBox = new Box2DPhysicsComponent( this->getWorld()->getPhysicsWorld(), this, b2_dynamicBody );
    physBox->setContactable( true );
    this->attachComponent( "PhysicsComponent", physBox );
}

void EnemyA::onHit( GameObject* hitBy, Contact contact )
{
    GameObject::onHit( hitBy, contact );

    if(hitBy && hitBy->getName() == "Fireball")
        this->setExpired( true );
}
