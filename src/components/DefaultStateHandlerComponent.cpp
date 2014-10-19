#include <lib/components/AnimationGraphicsComponent.hpp>
#include <lib/gameobjects/GameObject.hpp>
#include "lib/components/DefaultStateHandlerComponent.hpp"

DefaultStateHandlerComponent::DefaultStateHandlerComponent( GameObject* gameObject ) :
        mStates()
        , mGameObject( gameObject )
        , mCurrent( nullptr )
        , mPrevious( nullptr )
{

}

void DefaultStateHandlerComponent::update( GameObject* object, sf::Time dt )
{
    AnimationGraphicsComponent* animComp = dynamic_cast<AnimationGraphicsComponent*>(object->getGraphicComponent());
    if ( mCurrent->returnToPreviousState() && animComp->isAnimationFinished() )
    {
        changeToPreviousState( object );
    }

    if ( mCurrent->getFollowUpState() != "" && animComp->isAnimationFinished() )
    {
        setState( object, mCurrent->getFollowUpState() );
    }

}

bool DefaultStateHandlerComponent::changeState( GameObject* object, std::string state )
{
    if ( mCurrent->hasState( state ) )
    {
        mPrevious = mCurrent;
        mCurrent = &mStates.at( state );
        changeAnimation( object, mCurrent->getAnimation() );
        return true;
    }
    return false;
}

void DefaultStateHandlerComponent::changeToPreviousState( GameObject* object )
{
    if ( mPrevious )
        mCurrent = mPrevious;

    changeAnimation( object, mCurrent->getAnimation() );
}

std::string DefaultStateHandlerComponent::getCurrentState() const
{
    return mCurrent->getName();
}

std::string DefaultStateHandlerComponent::getPreviousState() const
{
    if ( mPrevious )
        return mPrevious->getName();
    else
        return "";
}

void DefaultStateHandlerComponent::setStartState( std::string start )
{
    mCurrent = &mStates.at( start );
}

void DefaultStateHandlerComponent::addState( std::string key, State state )
{
    mStates.emplace( key, state );
}

void DefaultStateHandlerComponent::setState( GameObject* object, std::string state )
{
    mPrevious = mCurrent;
    mCurrent = &mStates.at( state );
    changeAnimation( object, mCurrent->getAnimation() );
}

void DefaultStateHandlerComponent::changeAnimation( GameObject* object, std::string animation )
{
    AnimationGraphicsComponent* animComp = dynamic_cast<AnimationGraphicsComponent*>(object->getGraphicComponent());
    if ( animComp )
    {
        animComp->setAnimation( animation );
    }
}

GameObject* DefaultStateHandlerComponent::getGameObject() const
{
    return mGameObject;
}
