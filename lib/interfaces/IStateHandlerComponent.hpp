#ifndef ISTATE_HANDLER_COMPONENT_HPP
#define ISTATE_HANDLER_COMPONENT_HPP

#include <unordered_map>
#include <stdexcept>
#include <string>
#include "lib/State.hpp"

class GameObject;

class IStateHandlerComponent
{
public:
    void addState( std::string key, State state )
    {
        mStates.emplace( key, state );
    };

    void onAction( std::string action, GameObject& object )
    {
        std::string newState = mActiveState->onAction( action, object );

        if( newState != "")
        {
            try
            {
                mActiveState = &mStates.at( newState );
            }
            catch ( std::out_of_range )
            {
                // New State does not exist
            }
        }
    }

    void setStartState( std::string state )
    {
        try
        {
            mActiveState = &mStates.at( state );
        }
        catch ( std::out_of_range oor )
        {
            // Could not set start state
        }
    }

    const State* getActiveState() const
    {
        return mActiveState;
    }

protected:
    std::unordered_map<std::string, State> mStates;
    State* mActiveState;
};

#endif
