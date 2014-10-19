#include <lib/components/ProjectileMovementComponent.hpp>
#include <lib/components/HealthComponent.hpp>
#include <lib/components/AnimationGraphicsComponent.hpp>
#include <lib/components/PlayerMovementComponent.hpp>
#include <lib/components/EnemyAIComponent.hpp>
#include <lib/components/DefaultStateHandlerComponent.hpp>
#include <lib/components/PlayerInputComponent.hpp>
#include <lib/components/ActionComponent.hpp>
#include <lib/components/ProjectileAIComponent.hpp>
#include <lib/gameobjects/Slash.hpp>
#include <lib/components/SoundComponent.hpp>
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

    Animation attack( "attack" );
    attack.addFrame( sf::Vector2f( 10.f, 248.f ), sf::Vector2f( 22.f, 29.f ) );
    attack.addFrame( sf::Vector2f( 42.f, 247.f ), sf::Vector2f( 42.f, 30.f ) );
    attack.addFrame( sf::Vector2f( 84.f, 247.f ), sf::Vector2f( 43.f, 30.f ) );
    attack.addFrame( sf::Vector2f( 127.f, 248.f ), sf::Vector2f( 40.f, 29.f ) );
    attack.addFrame( sf::Vector2f( 174.f, 249.f ), sf::Vector2f( 28.f, 28.f ) );
    attack.addFrame( sf::Vector2f( 217.f, 248.f ), sf::Vector2f( 26.f, 29.f ) );
    attack.addFrame( sf::Vector2f( 258.f, 248.f ), sf::Vector2f( 27.f, 29.f ) );
    attack.addFrame( sf::Vector2f( 302.f, 249.f ), sf::Vector2f( 21.f, 28.f ) );
    attack.addFrame( sf::Vector2f( 348.f, 248.f ), sf::Vector2f( 19.f, 29.f ) );
    attack.addFrame( sf::Vector2f( 388.f, 248.f ), sf::Vector2f( 20.f, 29.f ) );
    attack.addFrame( sf::Vector2f( 431.f, 248.f ), sf::Vector2f( 21.f, 29.f ) );
    attack.addFrame( sf::Vector2f( 473.f, 248.f ), sf::Vector2f( 20.f, 29.f ) );
    attack.setTimePerFrame( 75 );
    attack.setRepeatable( false );
    agc->addAnimation( "attack", attack );

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

    PlayerMovementComponent* pmc = new PlayerMovementComponent( this );
    pmc->setJumpHeight( -2.5f );
    this->attachComponent( "MovementComponent", pmc );

    HealthComponent* health = new HealthComponent( this );
    /** No element **/
    health->addDamageResponse( "none",
            []( GameObject* object, float damage )
            {
                HealthComponent* hp = dynamic_cast<HealthComponent*>( object->getComponent( "HealthComponent" ) );
                if ( hp )
                {
                    hp->setHealth( hp->getHealth() - damage );
                }

                AnimationGraphicsComponent* graphics = dynamic_cast<AnimationGraphicsComponent*>( object->getGraphicComponent() );
                if( graphics )
                {
                    graphics->highlight();
                }
            }
    );
    /** Slash damage **/
    health->addDamageResponse( "slash",
            []( GameObject* object, float damage )
            {
                // Immune, do nothing
            }
    );
    this->attachComponent( "HealthComponent", health );

    /** Test for action components which can define their own actions **/
    ActionComponent* ac = new ActionComponent( this );
    ac->addAction(
            "shoot", []( GameObject* object )
    {
        sf::Vector2f velocity( 0.f, 0.f );
        sf::Vector2f size( 20.f, 30.f );
        sf::Vector2f pos = object->getPosition();

        Slash* projectile = dynamic_cast<Slash*>( object->getWorld()->createGameObject( "Slash", pos, size ) );
        ProjectileAIComponent* ai = dynamic_cast<ProjectileAIComponent*>( projectile->getComponent( "InputComponent" ) );
        if( ai )
        {
            ai->setMaxTimeAlive( 15 );
        }
        projectile->setMovementSpeed( velocity );
    } );
    this->attachComponent( "ActionComponent", ac );

    /** Sound component **/
    SoundComponent* sound = new SoundComponent( this );
    sf::Sound shoot;
    shoot.setBuffer( this->getWorld()->getSoundHolder()->get( "clap" ) );
    sound->addSound( "clap", shoot );
    this->attachComponent( "SoundComponent", sound );
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
            float val = atof( std::get<1>( property ).c_str() );
            movement->setMoveSpeed( val );
        }

        if ( std::get<0>( property ) == "acceleration" )
        {
            PlayerMovementComponent* movement = dynamic_cast<PlayerMovementComponent*>( this->getComponent( "MovementComponent" ) );
            movement->setAcceleration( atof( std::get<1>( property ).c_str() ) );
        }
    }


}
