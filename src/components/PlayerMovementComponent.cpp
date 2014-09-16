#include <lib/GameObject.hpp>
#include <lib/components/Box2DPhysicsComponent.hpp>
#include <lib/components/DefaultStateHandlerComponent.hpp>
#include "lib/components/PlayerMovementComponent.hpp"

PlayerMovementComponent::PlayerMovementComponent() :
        mMoveSpeed( 1.f )
        , mJumpHeight( -5.f )
        , mWallBounceStrength( 8.f )
        , mDelayThresholdAfterJump( 100 )
        , mCurrentDelayAfterJump( 100 )
        , mDelayThresholdAfterWallJump( 2000 )
        , mCurrentDelayAfterWallJump()
{
    this->setType( "MovementComponent" );
}

void PlayerMovementComponent::update( GameObject& object, sf::Time dt )
{
    IStateHandlerComponent* stateComp = dynamic_cast<IStateHandlerComponent*>(object.getComponent( "StateHandlerComponent" ) );
    IPhysicsComponent* physComp = dynamic_cast<IPhysicsComponent*>(object.getComponent( "PhysicsComponent" ));

    if ( physComp->isInAir() )
    {
        stateComp->changeState( object, "jump" );
    }

    if ( stateComp->getCurrentState() == "jump" )
    {
        if ( mCurrentDelayAfterJump > mDelayThresholdAfterJump )
        {
            if ( physComp )
            {
                if ( !physComp->isInAir() )
                {
                    stateComp->changeState( object, "land" );
                    mCurrentDelayAfterJump = 0;
                }
            }
        }

        mCurrentDelayAfterJump += dt.asMilliseconds();
    }
}

void PlayerMovementComponent::move( GameObject& object, Movement mov )
{
    IStateHandlerComponent* stateComp = dynamic_cast<IStateHandlerComponent*>(object.getComponent( "StateHandlerComponent" ) );
    IPhysicsComponent* physComp = dynamic_cast<IPhysicsComponent*>(object.getComponent( "PhysicsComponent" ) );
    if ( physComp )
    {
        if ( physComp->getBodyType() != b2_staticBody )
        {
            b2Vec2 vel = physComp->getLinearVelocity();

            if ( (!physComp->isInAir() && stateComp->getCurrentState() == "attack") || mov == Movement::Idle )
            {
                vel.x = 0.f;
            }
            else
            {
                if ( mov == Movement::Left )
                    vel.x = -mMoveSpeed;
                else if ( mov == Movement::Right )
                    vel.x = mMoveSpeed;
            }

            physComp->setLinearVelocity( vel );
        }
    }
}

void PlayerMovementComponent::jump( GameObject& object )
{
    IPhysicsComponent* physComp = dynamic_cast<IPhysicsComponent*>(object.getComponent( "PhysicsComponent" ) );
    if ( physComp )
    {
        if ( !physComp->isInAir() )
        {
            if ( physComp->getBodyType() != b2_staticBody )
            {
                b2Vec2 vel = physComp->getLinearVelocity();
                vel.y = mJumpHeight;

                physComp->setLinearVelocity( vel );
            }
        }
    }
}

void PlayerMovementComponent::wallJump( GameObject& object )
{
    IPhysicsComponent* physComp = dynamic_cast<IPhysicsComponent*>(object.getComponent( "PhysicsComponent" ) );
    if ( physComp )
    {
        if( mCurrentDelayAfterWallJump.getElapsedTime().asMilliseconds() > mDelayThresholdAfterWallJump )
        {
            Collision col = physComp->hitWall();
            if ( col != Collision::None )
            {
                // TODO: Rework walking with impulses instead of setVelocity()
                b2Vec2 vel = physComp->getLinearVelocity();
                vel.x = (col == Collision::Left) ? mWallBounceStrength : -mWallBounceStrength;
                vel.y = mJumpHeight;
                physComp->setLinearVelocity( vel );
                mCurrentDelayAfterWallJump.restart();
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
