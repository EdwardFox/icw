#include <lib/GameObject.hpp>
#include <lib/components/Box2DPhysicsComponent.hpp>
#include <lib/components/DefaultStateHandlerComponent.hpp>
#include "lib/components/PlayerMovementComponent.hpp"

PlayerMovementComponent::PlayerMovementComponent( GameObject* gameObject ) :
        mMoveSpeed( 5.f )
        , mGameObject( gameObject )
        , mAcceleration( 0.1f )
        , mFriction( 0.f )
        , mJumpHeight( -1.0f )
        , mWallBounceStrength( 1.25f )
        , mDelayThresholdAfterJump( 100 )
        , mCurrentDelayAfterJump( 100 )
{
    this->setType( "MovementComponent" );
}

void PlayerMovementComponent::update( GameObject* object, sf::Time dt )
{
    IStateHandlerComponent* stateComp = dynamic_cast<IStateHandlerComponent*>(object->getComponent( "StateHandlerComponent" ) );
    IPhysicsComponent* physComp = dynamic_cast<IPhysicsComponent*>(object->getComponent( "PhysicsComponent" ));

    if ( physComp )
    {
        if ( physComp->isInAir() )
        {
            if ( stateComp )
            {
                stateComp->changeState( object, "jump" );
            }

            physComp->setFriction( 0.f );
        }
    }

    if ( physComp )
    {
        if ( !physComp->isInAir() )
        {
            physComp->setFriction( mFriction );
            if ( mCurrentDelayAfterJump > mDelayThresholdAfterJump )
            {
                stateComp->changeState( object, "land" );
                mCurrentDelayAfterJump = 0;
            }
            mCurrentDelayAfterJump += dt.asMilliseconds();
        }
    }
}

void PlayerMovementComponent::move( GameObject* object, Movement mov )
{
    IStateHandlerComponent* stateComp = dynamic_cast<IStateHandlerComponent*>(object->getComponent( "StateHandlerComponent" ) );
    IPhysicsComponent* physComp = dynamic_cast<IPhysicsComponent*>(object->getComponent( "PhysicsComponent" ) );
    if ( physComp )
    {
        if ( physComp->getBodyType() != b2_staticBody )
        {

            if ( (!physComp->isInAir() && stateComp->getCurrentState() == "attack") || mov == Movement::Idle )
            {
                b2Vec2 vel = physComp->getLinearVelocity();
                vel.x = 0.f;
                physComp->setLinearVelocity( vel );
            }
            else
            {
                if ( mov == Movement::Left )
                {
                    physComp->addLinearImpulse( b2Vec2( -mAcceleration, 0.f ) );
                    if ( physComp->getLinearVelocity().x < -mMoveSpeed )
                        physComp->setLinearVelocity( b2Vec2( -mMoveSpeed, physComp->getLinearVelocity().y ) );
                }
                else if ( mov == Movement::Right )
                {
                    physComp->addLinearImpulse( b2Vec2( mAcceleration, 0.f ) );
                    if ( physComp->getLinearVelocity().x > mMoveSpeed )
                        physComp->setLinearVelocity( b2Vec2( mMoveSpeed, physComp->getLinearVelocity().y ) );
                }
            }

        }
    }
}

void PlayerMovementComponent::jump( GameObject* object )
{
    IPhysicsComponent* physComp = dynamic_cast<IPhysicsComponent*>(object->getComponent( "PhysicsComponent" ) );
    if ( physComp )
    {
        if ( !physComp->isInAir() )
        {
            if ( physComp->getBodyType() != b2_staticBody )
            {
                b2Vec2 vel = physComp->getLinearVelocity();
                physComp->setLinearVelocity( b2Vec2( vel.x, 0.f ) );
                physComp->addLinearImpulse( b2Vec2( 0.f, mJumpHeight ) );
                physComp->setFriction( 0.f );
            }
        }
    }
}

float PlayerMovementComponent::getMoveSpeed() const
{
    return mMoveSpeed;
}

void PlayerMovementComponent::setMoveSpeed( float movespeed )
{
    mMoveSpeed = movespeed;
}

float PlayerMovementComponent::getAcceleration() const
{
    return mAcceleration;
}

void PlayerMovementComponent::setAcceleration( float accel )
{
    mAcceleration = accel;
}

float PlayerMovementComponent::getFriction() const
{
    return mFriction;
}

void PlayerMovementComponent::setFriction( float friction )
{
    mFriction = friction;
}

float PlayerMovementComponent::getJumpHeight() const
{
    return mJumpHeight;
}

void PlayerMovementComponent::setJumpHeight( float jumpheight )
{
    mJumpHeight = jumpheight;
}

int PlayerMovementComponent::getDelayThresholdAfterJump() const
{
    return mDelayThresholdAfterJump;
}

void PlayerMovementComponent::setDelayThresholdAfterJump( float delay )
{
    mDelayThresholdAfterJump = delay;
}

int PlayerMovementComponent::getCurrentDelayAfterJump() const
{
    return mCurrentDelayAfterJump;
}

void PlayerMovementComponent::setCurrentDelayAfterJump( float delay )
{
    mCurrentDelayAfterJump = delay;
}

GameObject* PlayerMovementComponent::getGameObject() const
{
    return mGameObject;
}
