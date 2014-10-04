#include <lib/components/ProjectileMovementComponent.hpp>
#include <lib/components/HealthComponent.hpp>
#include <lib/components/AnimationGraphicsComponent.hpp>
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

    sf::Texture& tex = this->getWorld()->getTextureHolder()->get( "golem" );
    AnimationGraphicsComponent* agc = new AnimationGraphicsComponent( this );
    agc->setTexture( &tex );

    Animation idle( "idle" );
    idle.addFrame( sf::Vector2f( 0.f, 0.f ), sf::Vector2f( 6.f, 11.f ) );
    idle.setTimePerFrame( 100000 );
    agc->addAnimation( "idle", idle );

    Animation run( "run" );
    run.addFrame( sf::Vector2f( 0.f, 22.f ), sf::Vector2f( 7.f, 11.f ) );
    run.addFrame( sf::Vector2f( 10.f, 22.f ), sf::Vector2f( 5.f, 11.f ) );
    run.addFrame( sf::Vector2f( 19.f, 22.f ), sf::Vector2f( 4.f, 11.f ) );
    run.addFrame( sf::Vector2f( 27.f, 22.f ), sf::Vector2f( 6.f, 11.f ) );
    run.addFrame( sf::Vector2f( 35.f, 22.f ), sf::Vector2f( 8.f, 11.f ) );
    run.addFrame( sf::Vector2f( 45.f, 22.f ), sf::Vector2f( 6.f, 11.f ) );
    run.addFrame( sf::Vector2f( 55.f, 22.f ), sf::Vector2f( 5.f, 11.f ) );
    run.addFrame( sf::Vector2f( 64.f, 22.f ), sf::Vector2f( 5.f, 11.f ) );
    run.setTimePerFrame( 50 );
    agc->addAnimation( "run", run );

    agc->setAnimation( "idle" );
    this->setGraphicComponent( agc );



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
