#ifndef DEFAULT_STATE_HANDLER_COMPONENT_HPP
#define DEFAULT_STATE_HANDLER_COMPONENT_HPP

#include "lib/interfaces/IComponent.hpp"
#include "lib/interfaces/IStateHandlerComponent.hpp"
#include "lib/State.hpp"
#include <unordered_map>

class DefaultStateHandlerComponent : public IComponent, public IStateHandlerComponent
{
public:
    DefaultStateHandlerComponent( GameObject* gameObject);

    virtual ~DefaultStateHandlerComponent() {};

    virtual GameObject* getGameObject() const override;

    virtual void update( GameObject* object, sf::Time dt ) override;

    virtual void changeState( GameObject* object, std::string state ) override;

    virtual void changeToPreviousState( GameObject* object ) override;

    virtual std::string getCurrentState() const override;

    virtual std::string getPreviousState() const override;

    virtual void setStartState( std::string start ) override;

    virtual void addState( std::string key, State state ) override;

protected:
    virtual void setState( GameObject* object, std::string state ) override;

private:
    void changeAnimation( GameObject* object, std::string animation );

    std::unordered_map<std::string, State> mStates;
    GameObject* mGameObject;
    State* mCurrent;
    State* mPrevious;
};

#endif
