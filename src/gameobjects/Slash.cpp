#include <lib/components/ProjectileMovementComponent.hpp>
#include <lib/components/HealthComponent.hpp>
#include "lib/gameobjects/Slash.hpp"
#include "lib/components/SolidColorGraphicsComponent.hpp"
#include "lib/components/Box2DPhysicsComponent.hpp"
#include "lib/components/ProjectileAIComponent.hpp"
#include "lib/World.hpp"

Slash::Slash( World* world, std::string name, sf::Vector2f position, sf::Vector2f size ) :
        GameObject( world, name, position, size )
{
    createDefaultComponents();
}

void Slash::createDefaultComponents()
{
    SolidColorGraphicsComponent* solid = new SolidColorGraphicsComponent( this, this->getSize() );
    solid->setDrawn( false );
    this->setGraphicComponent( solid );

    Box2DPhysicsComponent* box = new Box2DPhysicsComponent( this );
    box->createCollisionBody( this->getWorld()->getPhysicsWorld(), this, b2_dynamicBody, true );
    box->setContactable( true );
    box->setGravityScale( 0.f );
    this->attachComponent( "PhysicsComponent", box );

    ProjectileAIComponent* proj = new ProjectileAIComponent( this );
    this->attachComponent( "InputComponent", proj );

    ProjectileMovementComponent* move = new ProjectileMovementComponent( this );
    move->setMoveSpeed( sf::Vector2f( 10.f, 0.f ) );
    this->attachComponent( "MovementComponent", move );
}

void Slash::onHit( GameObject* hitBy, Contact contact )
{
    GameObject::onHit( hitBy, contact );

    bool shouldExpire = false;

    if ( Contact::Begin == contact && hitBy )
    {
        HealthComponent* enemyHP = dynamic_cast<HealthComponent*>( hitBy->getComponent( "HealthComponent" ) );
        if ( enemyHP )
        {
            enemyHP->receiveDamage( "slash", 10.f );
        }

        shouldExpire = (hitBy->getName() == "EnemyA") ? false : true;
    }

    this->setExpired( shouldExpire );
}

void Slash::setMovementSpeed( sf::Vector2f movespeed )
{
    IProjectileMovementComponent* move = dynamic_cast<IProjectileMovementComponent*>( this->getComponent( "MovementComponent" ) );
    if ( move )
    {
        move->setMoveSpeed( movespeed );
    }
}
