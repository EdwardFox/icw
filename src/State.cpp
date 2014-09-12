#include "lib/State.hpp"
#include <stdexcept>

State::State( std::string state ) :
        mActions()
        , mStateName( state )
{

}

std::string State::onAction( std::string action, GameObject& object )
{
    try
    {
        std::string nextState = mActions.at( action )( object );
        return nextState;
    }
    catch ( std::out_of_range oor )
    {
        return "";
    }
}

void State::addAction( std::string key, std::function<std::string( GameObject& object )> action )
{
    mActions.emplace( key, action );
}
