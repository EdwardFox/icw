#ifndef PLAYER_MOVEMENT_COMPONENT_HPP
#define PLAYER_MOVEMENT_COMPONENT_HPP

#include "lib/interfaces/IComponent.hpp"
#include "lib/interfaces/IMovementComponent.hpp"

class DefaultMovementComponent : public IComponent, public IMovementComponent
{
public:
    DefaultMovementComponent();

    virtual void update( GameObject& object, sf::Time dt );

    virtual float getMoveSpeed() const;

    virtual void setMoveSpeed( float movespeed );

    virtual float getJumpHeight() const;

    virtual void setJumpHeight( float jumpheight );

private:
    virtual void move( GameObject& object, Movement mov );

    virtual void jump( GameObject& object );

    virtual void land( GameObject& object );

    float mMoveSpeed;
    float mJumpHeight;
};

#endif
