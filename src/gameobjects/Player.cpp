#include <lib/World.hpp>
#include <lib/components/AnimationGraphicsComponent.hpp>
#include <lib/components/DefaultStateHandlerComponent.hpp>
#include <lib/components/Box2DPhysicsComponent.hpp>
#include <lib/components/PlayerInputComponent.hpp>
#include <lib/components/PlayerMovementComponent.hpp>
#include <lib/components/ActionComponent.hpp>
#include <lib/gameobjects/Fireball.hpp>
#include <lib/components/SoundComponent.hpp>
#include <lib/components/HealthComponent.hpp>
#include "lib/gameobjects/Player.hpp"


Player::Player( World* world, std::string name, sf::Vector2f position, sf::Vector2f size ) :
        GameObject( world, name, position, size )
{
    createDefaultComponents();
}

void Player::createDefaultComponents()
{
    World* world = this->getWorld();

    /** Animation **/
    sf::Texture& tex = world->getTextureHolder()->get( "ror" );
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

    Animation jump( "jump" );
    jump.addFrame( sf::Vector2f( 0.f, 11.f ), sf::Vector2f( 9.f, 11.f ) );
    jump.setTimePerFrame( 10000 );
    agc->addAnimation( "jump", jump );

    Animation attack( "attack" );
    attack.addFrame( sf::Vector2f( 0.f, 33.f ), sf::Vector2f( 56.f, 11.f ) );
    attack.addFrame( sf::Vector2f( 65.f, 33.f ), sf::Vector2f( 61.f, 11.f ) );
    attack.addFrame( sf::Vector2f( 129.f, 33.f ), sf::Vector2f( 62.f, 11.f ) );
    attack.addFrame( sf::Vector2f( 194.f, 33.f ), sf::Vector2f( 57.f, 11.f ) );
    attack.addFrame( sf::Vector2f( 258.f, 33.f ), sf::Vector2f( 14.f, 11.f ) );
    attack.setRepeatable( false );
    attack.setTimePerFrame( 15 );
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



    /** Add a physics component with fixed rotations and default sensors **/
    Box2DPhysicsComponent* dynPhysics = new Box2DPhysicsComponent( this );
    dynPhysics->createCollisionBody( world->getPhysicsWorld(), this, b2_dynamicBody, false );
    dynPhysics->setFixedRotation( true );
    dynPhysics->createDefaultSensors( world->getPhysicsWorld(), this );
    dynPhysics->setContactable( true );
    this->attachComponent( "PhysicsComponent", dynPhysics );

    PlayerInputComponent* tic = new PlayerInputComponent( this );
    this->attachComponent( "InputComponent", tic );

    PlayerMovementComponent* pmc = new PlayerMovementComponent( this );
    this->attachComponent( "MovementComponent", pmc );



    /** Test for action components which can define their own actions **/
    ActionComponent* ac = new ActionComponent( this );
    ac->addAction(
            "shoot", []( GameObject* object )
    {
        sf::Vector2f velocity( 10.f, 0.f );
        sf::Vector2f size( 1.f, 1.f );
        sf::Vector2f pos = object->getPosition();

        float offsetX = 15.f;

        /**
        * Figure out in which direction the player is looking
        * and modify values accordingly
        * TODO: Find a better place for this information than the animation component
        */
        AnimationGraphicsComponent* animComp = dynamic_cast<AnimationGraphicsComponent*>(object->getGraphicComponent());
        if ( animComp )
        {
            if ( animComp->getFlipped().x == -1.f )
            {
                offsetX = -offsetX;
                velocity.x = -velocity.x;
            }
        }

        pos.x += offsetX;
        pos.y -= 3.f; // Adjust position

        Fireball* projectile = dynamic_cast<Fireball*>( object->getWorld()->createGameObject( "Fireball", pos, size ) );
        projectile->setMovementSpeed( velocity );
    } );
    this->attachComponent( "ActionComponent", ac );

    HealthComponent* health = new HealthComponent( this );
    /** Slash damage **/
    health->addDamageResponse( "slash",
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
    this->attachComponent( "HealthComponent", health );

    /** Sound component **/
    SoundComponent* sound = new SoundComponent( this );
    sf::Sound shoot;
    shoot.setBuffer( world->getSoundHolder()->get( "shoot" ) );
    sound->addSound( "shoot", shoot );
    this->attachComponent( "SoundComponent", sound );
}

void Player::onHit( GameObject* hitBy, Contact contact )
{
    GameObject::onHit( hitBy, contact );
}
