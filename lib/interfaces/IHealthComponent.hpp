#ifndef IHEALTH_COMPONENT_HPP
#define IHEALTH_COMPONENT_HPP

#include <string>
#include <functional>

class GameObject;

class IHealthComponent
{
public:

    virtual ~IHealthComponent()
    {
    };

    virtual float getHealth() const = 0;

    virtual float getMaximumHealth() const = 0;

    virtual void receiveDamage( std::string element, float damage ) = 0;

    virtual void addDamageResponse( std::string element, std::function<void( GameObject* object, float damage )> ) = 0;

    virtual void setHealth( float health ) = 0;

    virtual void setMaximumHealth( float health ) = 0;

};

#endif