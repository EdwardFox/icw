#ifndef ISTATE_HANDLER_COMPONENT_HPP
#define ISTATE_HANDLER_COMPONENT_HPP

#include <string>

class GameObject;

class State;

class IStateHandlerComponent
{
public:

    virtual ~IStateHandlerComponent() {};

    virtual bool changeState( GameObject* object, std::string state ) = 0;

    virtual void changeToPreviousState( GameObject* object ) = 0;

    virtual std::string getCurrentState() const = 0;

    virtual std::string getPreviousState() const = 0;

    virtual void setStartState( std::string start ) = 0;

    virtual void addState( std::string key, State state ) = 0;

protected:
    virtual void setState( GameObject* object, std::string state ) = 0;
};

#endif