#include <lib/components/ProjectileMovementComponent.hpp>
#include <lib/components/HealthComponent.hpp>
#include <lib/components/AnimationGraphicsComponent.hpp>
#include <lib/components/PlayerMovementComponent.hpp>
#include <lib/components/EnemyAIComponent.hpp>
#include <lib/components/DefaultStateHandlerComponent.hpp>
#include <lib/components/PlayerInputComponent.hpp>
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
    idle.addFrame( sf::Vector2f( 0.f, 91.f ), sf::Vector2f( 20.f, 29.f ) );
    idle.setTimePerFrame( 100000 );
    agc->addAnimation( "idle", idle );

    Animation run( "run" );
    run.addFrame( sf::Vector2f( 0.f, 329.f ), sf::Vector2f( 20.f, 28.f ) );
    run.addFrame( sf::Vector2f( 20.f, 328.f ), sf::Vector2f( 20.f, 29.f ) );
    run.addFrame( sf::Vector2f( 40.f, 327.f ), sf::Vector2f( 20.f, 30.f ) );
    run.addFrame( sf::Vector2f( 60.f, 329.f ), sf::Vector2f( 20.f, 28.f ) );
    run.addFrame( sf::Vector2f( 80.f, 328.f ), sf::Vector2f( 20.f, 29.f ) );
    run.addFrame( sf::Vector2f( 100.f, 327.f ), sf::Vector2f( 20.f, 31.f ) );
    run.setTimePerFrame( 100 );
    agc->addAnimation( "run", run );

    agc->setAnimation( "idle" );
    this->setGraphicComponent( agc );




    /** States **/
    State idleState;
    idleState.setName( "idle" );
    idleState.setAnimation( "idle" );
    idleState.addState( "run" );
    idleState.addState( "jump" );
    idleState.addState( "attack" );

    State runState;
    runState.setName( "run" );
    runState.setAnimation( "run" );
    runState.addState( "idle" );
    runState.addState( "jump" );
    runState.addState( "attack" );

    State jumpState;
    jumpState.setName( "jump" );
    jumpState.setAnimation( "jump" );
    jumpState.addState( "land" );
    jumpState.addState( "attack" );

    State landState;
    landState.setName( "land" );
    landState.setAnimation( "idle" );
    landState.addState( "idle" );
    landState.addState( "run" );
    landState.addState( "attack" );

    State attackState;
    attackState.setName( "attack" );
    attackState.setAnimation( "attack" );
    attackState.setReturnToPreviousState( true );

    DefaultStateHandlerComponent* dsc = new DefaultStateHandlerComponent( this );
    dsc->addState( "idle", idleState );
    dsc->addState( "run", runState );
    dsc->addState( "jump", jumpState );
    dsc->addState( "land", landState );
    dsc->addState( "attack", attackState );
    dsc->setStartState( "idle" );

    this->attachComponent( "StateHandlerComponent", dsc );


    EnemyAIComponent* ai = new EnemyAIComponent( this );
    this->attachComponent( "InputComponent", ai );


    Box2DPhysicsComponent* physBox = new Box2DPhysicsComponent( this );
    physBox->createCollisionBody( this->getWorld()->getPhysicsWorld(), this, b2_dynamicBody, false );
    physBox->setContactable( true );
    physBox->setFixedRotation( true );
    physBox->createDefaultSensors( this->getWorld()->getPhysicsWorld(), this );
    this->attachComponent( "PhysicsComponent", physBox );

    HealthComponent* health = new HealthComponent( this );

    PlayerMovementComponent* pmc = new PlayerMovementComponent( this );
    this->attachComponent( "MovementComponent", pmc );

    /** No element **/
    health->addDamageResponse( "none",
            []( GameObject* object, float damage )
            {
                HealthComponent* hp = dynamic_cast<HealthComponent*>( object->getComponent( "HealthComponent" ) );
                if ( hp )
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


void EnemyA::setProperties( std::vector<std::tuple<std::string, std::string>> properties )
{
    GameObject::setProperties( properties );

    for ( std::tuple<std::string, std::string> property : properties )
    {
        if ( std::get<0>( property ) == "hp" )
        {
            HealthComponent* health = dynamic_cast<HealthComponent*>( this->getComponent( "HealthComponent" ) );
            health->setMaximumHealth( atof( std::get<1>( property ).c_str() ) );
        }

        if ( std::get<0>( property ) == "speed" )
        {
            PlayerMovementComponent* movement = dynamic_cast<PlayerMovementComponent*>( this->getComponent( "MovementComponent" ) );
            movement->setMoveSpeed( atof( std::get<1>( property ).c_str() ) );
        }

        if ( std::get<0>( property ) == "acceleration" )
        {
            PlayerMovementComponent* movement = dynamic_cast<PlayerMovementComponent*>( this->getComponent( "MovementComponent" ) );
            movement->setAcceleration( atof( std::get<1>( property ).c_str() ) );
        }
    }


}
