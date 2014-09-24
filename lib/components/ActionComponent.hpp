#ifndef ACTION_COMPONENT_HPP
#define ACTION_COMPONENT_HPP

#include <unordered_map>
#include "lib/interfaces/IComponent.hpp"
#include "lib/interfaces/IActionComponent.hpp"

class ActionComponent : public IComponent, public IActionComponent
{
public:
    ActionComponent();

    virtual ~ActionComponent() {};

    virtual void update( GameObject& object, sf::Time dt );

    virtual void addAction( std::string key, std::function<void( GameObject& object )> action );

    virtual void executeAction( std::string key, GameObject& object );

private:
    std::unordered_map<std::string, std::function<void( GameObject& object )>> mActions;

};

#endif

