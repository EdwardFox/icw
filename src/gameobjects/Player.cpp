#include <lib/World.hpp>
#include <lib/components/AnimationGraphicsComponent.hpp>
#include <lib/components/DefaultStateHandlerComponent.hpp>
#include <lib/components/Box2DPhysicsComponent.hpp>
#include <lib/components/PlayerInputComponent.hpp>
#include <lib/components/PlayerMovementComponent.hpp>
#include <lib/components/ActionComponent.hpp>
#include <lib/gameobjects/Fireball.hpp>
#include "lib/gameobjects/Player.hpp"


Player::Player( World* world, std::string name, sf::Vector2f position, sf::Vector2f size ) :
        GameObject( world, name, position, size )
{
    createDefaultComponents();
}

void Player::createDefaultComponents()
{
    World* world = this->getWorld();
    const Map* map = world->getMap();

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
    attack.setTimePerFrame( 1 );
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
    Box2DPhysicsComponent* dynPhysics = new Box2DPhysicsComponent( world->getPhysicsWorld(), this, b2_dynamicBody );
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
        sf::Vector2f size( 4.f, 4.f );
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

        /** Create a bunch of projectiles that fly in different directions **/
        for ( float i = 3.f; i > -4.f; --i )
        {
            sf::Vector2f pos2 = pos;
            pos2.y += i * 5;
            velocity.y = i;

            Fireball* projectile = dynamic_cast<Fireball*>( object->getWorld()->createGameObject( "Fireball", pos2, size ) );
            projectile->setMovementSpeed( velocity );
        }
    } );
    this->attachComponent( "ActionComponent", ac );
}

void Player::onHit( GameObject* hitBy, Contact contact )
{

}