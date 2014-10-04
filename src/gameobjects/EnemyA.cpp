#include <lib/components/ProjectileMovementComponent.hpp>
#include <lib/components/HealthComponent.hpp>
#include "lib/gameobjects/EnemyA.hpp"
#include "lib/components/SolidColorGraphicsComponent.hpp"
#include "lib/components/Box2DPhysicsComponent.hpp"
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

    Box2DPhysicsComponent* physBox = new Box2DPhysicsComponent( this );
    physBox->createCollisionBody( this->getWorld()->getPhysicsWorld(), this, b2_dynamicBody, false );
    physBox->setContactable( true );
    this->attachComponent( "PhysicsComponent", physBox );

    HealthComponent* health = new HealthComponent( this );
    health->setHealth( 100.f );
    health->setMaximumHealth( 100.f );

    /** No element **/
    health->addDamageResponse( "none",
            []( GameObject* object, float damage )
            {
                HealthComponent* hp = dynamic_cast<HealthComponent*>( object->getComponent( "HealthComponent" ) );
                if( hp )
                {
                    hp->setHealth( hp->getHealth() - damage );
                }
            }
    );
    this->attachComponent( "HealthComponent", health );
}

void EnemyA::onHit( GameObject* hitBy, Contact contact )
{
    GameObject::onHit( hitBy, contact );

//    if(hitBy && hitBy->getName() == "Fireball")
//        this->setExpired( true );
}
