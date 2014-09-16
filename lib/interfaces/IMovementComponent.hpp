#ifndef IMOVEMENT_COMPONENT_HPP
#define IMOVEMENT_COMPONENT_HPP

#include "lib/Data.hpp"

class GameObject;

class IMovementComponent
{
public:
    virtual void move( GameObject& object, Movement mov ) = 0;

    virtual void jump( GameObject& object ) = 0;

    virtual float getMoveSpeed() const = 0;

    virtual void setMoveSpeed( float movespeed ) = 0;

    virtual float getJumpHeight() const = 0;

    virtual void setJumpHeight( float jumpheight ) = 0;

    virtual int getDelayThresholdAfterJump() const = 0;

    virtual void setDelayThresholdAfterJump( float delay ) = 0;

    virtual int getCurrentDelayAfterJump() const = 0;

    virtual void setCurrentDelayAfterJump( float delay ) = 0;

protected:
};

#endif
