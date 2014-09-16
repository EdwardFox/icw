#ifndef DEFAULT_STATE_HANDLER_COMPONENT_HPP
#define DEFAULT_STATE_HANDLER_COMPONENT_HPP

#include "lib/interfaces/IComponent.hpp"
#include "lib/interfaces/IStateHandlerComponent.hpp"
#include "lib/State.hpp"
#include <unordered_map>

class DefaultStateHandlerComponent : public IComponent, public IStateHandlerComponent
{
public:
    DefaultStateHandlerComponent();

    virtual void update( GameObject& object, sf::Time dt );

    virtual void changeState( GameObject& object, std::string state );

    virtual void changeToPreviousState( GameObject& object );

    virtual std::string getCurrentState() const;

    virtual std::string getPreviousState() const;

    virtual void setStartState( std::string start );

    virtual void addState( std::string key, State state );

protected:
    virtual void setState( GameObject& object, std::string state );

private:
    void changeAnimation( GameObject& object, std::string animation );

    std::unordered_map<std::string, State> mStates;
    State* mCurrent;
    State* mPrevious;
};

#endif
