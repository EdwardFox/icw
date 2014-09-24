#ifndef IACTION_COMPONENT_HPP
#define IACTION_COMPONENT_HPP

#include <string>
#include <functional>

class GameObject;

class IActionComponent
{
public:

    virtual ~IActionComponent() {};

    virtual void addAction( std::string key, std::function<void( GameObject& object )> action ) = 0;

    virtual void executeAction( std::string key, GameObject& object ) = 0;

};

#endif