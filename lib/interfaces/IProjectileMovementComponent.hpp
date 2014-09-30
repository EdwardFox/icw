#ifndef IPROJECTILE_MOVEMENT_COMPONENT
#define IPROJECTILE_MOVEMENT_COMPONENT

#include <SFML/System/Vector2.hpp>
#include "lib/Data.hpp"

class GameObject;

class IProjectileMovementComponent
{
public:

    virtual ~IProjectileMovementComponent()
    {
    };

    virtual void move( GameObject* object ) = 0;

    virtual sf::Vector2f getMoveSpeed() const = 0;

    virtual void setMoveSpeed( sf::Vector2f movespeed ) = 0;
};

#endif
