#include "lib/State.hpp"
#include <stdexcept>

State::State() :
        mName( "" )
        , mAnimation( "" )
        , mFollowUpState( "" )
        , mFollowStates()
        , mReturnToPreviousState( false )
{

}

std::string State::getName() const
{
    return mName;
}

void State::setName( std::string name )
{
    mName = name;
}

std::string State::getAnimation() const
{
    return mAnimation;
}

void State::setAnimation( std::string anim )
{
    mAnimation = anim;
}

bool State::hasState( std::string state ) const
{
    bool exists = false;

    try
    {
        mFollowStates.at( state );
        exists = true;
    }
    catch ( std::out_of_range oor )
    {
        // Does not exist
    }

    return exists;
}

void State::addState( std::string state )
{
    mFollowStates.emplace( state, state );
}

bool State::returnToPreviousState() const
{
    return mReturnToPreviousState;
}

void State::setReturnToPreviousState( bool ret )
{
    mReturnToPreviousState = ret;
}

std::string State::getFollowUpState() const
{
    return mFollowUpState;
}

void State::setFollowUpState( std::string follow )
{
    mFollowUpState = follow;
}
