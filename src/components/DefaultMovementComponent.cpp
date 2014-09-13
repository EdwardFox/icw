#include <lib/GameObject.hpp>
#include <lib/components/Box2DPhysicsComponent.hpp>
#include "lib/components/DefaultMovementComponent.hpp"
#include "lib/components/DefaultStateHandlerComponent.hpp"
#include "lib/interfaces/IPhysicsComponent.hpp"

DefaultMovementComponent::DefaultMovementComponent() :
        mMoveSpeed( 10.f )
        , mJumpHeight( -7.5f )
{

}

void DefaultMovementComponent::update( GameObject& object, sf::Time dt )
{
    IComponent* comp = object.getComponent( "StateHandlerComponent" );
    if ( DefaultStateHandlerComponent* stateComp = dynamic_cast<DefaultStateHandlerComponent*>(comp) )
    {
        std::string state = stateComp->getActiveState()->getStateName();
        if ( state == "runLeft" || state == "fallLeft" )
            move( object, Movement::Left );

        if ( state == "runRight" || state == "fallRight" )
            move( object, Movement::Right );

        if ( state == "idle" )
            move( object, Movement::Idle );

        if ( state == "jump" )
            jump( object );

        if ( state == "fall" || state == "fallLeft" || state == "fallRight" )
            land( object );
    }
}

void DefaultMovementComponent::move( GameObject& object, Movement mov )
{
    // Tell the physics component to move the player
    ComponentCommand<IPhysicsComponent&> physicsCommand;
    physicsCommand.targetType = "PhysicsComponent";
    physicsCommand.execute = [mov, this]( IPhysicsComponent& comp )
    {
        if ( comp.getBodyType() != b2_staticBody )
        {
            b2Vec2 vel = comp.getLinearVelocity();

            if ( mov == Movement::Left )
                vel.x = -mMoveSpeed;
            else if ( mov == Movement::Right )
                vel.x = mMoveSpeed;
            else
                vel.x = 0.f;

            comp.setLinearVelocity( vel );
        }
    };
    object.broadcastComponentCommand( physicsCommand );
}

void DefaultMovementComponent::jump( GameObject& object )
{
    // Tell the physics component to move the player
    ComponentCommand<IPhysicsComponent&> physicsCommand;
    physicsCommand.targetType = "PhysicsComponent";
    physicsCommand.execute = [this]( IPhysicsComponent& comp )
    {
        if ( comp.getBodyType() != b2_staticBody )
        {
            b2Vec2 vel = comp.getLinearVelocity();
            vel.y = mJumpHeight;

            comp.setLinearVelocity( vel );
        }
    };
    object.broadcastComponentCommand( physicsCommand );

    // Tell the state component to change state accordingly
    ComponentCommand<IStateHandlerComponent&> stateCommand;
    stateCommand.targetType = "StateHandlerComponent";
    stateCommand.execute = [&object]( IStateHandlerComponent& comp )
    {
        comp.onAction( "fall", object );
    };
    object.broadcastComponentCommand( stateCommand );
}

void DefaultMovementComponent::land( GameObject& object )
{
    IComponent* comp = object.getComponent( "PhysicsComponent" );
    if ( Box2DPhysicsComponent* boxComp = dynamic_cast<Box2DPhysicsComponent*>(comp) )
    {
        if ( boxComp->getPhysicsGroundContactListener()->getNumGroundContacts() > 0 )
        {
            // Tell the state component to change state accordingly
            ComponentCommand<IStateHandlerComponent&> stateCommand;
            stateCommand.targetType = "StateHandlerComponent";
            stateCommand.execute = [&object]( IStateHandlerComponent& comp )
            {
                comp.onAction( "hitGround", object );
            };
            object.broadcastComponentCommand( stateCommand );
        }
    }

}

float DefaultMovementComponent::getMoveSpeed() const
{
    return mMoveSpeed;
}

void DefaultMovementComponent::setMoveSpeed( float movespeed )
{
    mMoveSpeed = movespeed;
}

float DefaultMovementComponent::getJumpHeight() const
{
    return mJumpHeight;
}

void DefaultMovementComponent::setJumpHeight( float jumpheight )
{
    mJumpHeight = jumpheight;
}
