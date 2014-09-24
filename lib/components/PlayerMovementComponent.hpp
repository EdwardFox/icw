#ifndef PLAYER_MOVEMENT_COMPONENT_HPP
#define PLAYER_MOVEMENT_COMPONENT_HPP

#include "lib/interfaces/IComponent.hpp"
#include "lib/interfaces/IMovementComponent.hpp"

class PlayerMovementComponent : public IComponent, public IMovementComponent
{
public:
    PlayerMovementComponent();

    virtual ~PlayerMovementComponent() {};

    virtual void move( GameObject& object, Movement mov );

    virtual void jump( GameObject& object );

    virtual void update( GameObject& object, sf::Time dt );

    virtual float getMoveSpeed() const;

    virtual void setMoveSpeed( float movespeed );

    virtual float getAcceleration() const;

    virtual void setAcceleration( float accel );

    virtual float getFriction() const;

    virtual void setFriction( float friction );

    virtual float getJumpHeight() const;

    virtual void setJumpHeight( float jumpheight );

    virtual int getDelayThresholdAfterJump() const;

    virtual void setDelayThresholdAfterJump( float delay );

    virtual int getCurrentDelayAfterJump() const;

    virtual void setCurrentDelayAfterJump( float delay );

private:
    float mMoveSpeed;
    float mAcceleration;
    float mFriction;
    float mJumpHeight;
    float mWallBounceStrength;
    int mDelayThresholdAfterJump;
    int mCurrentDelayAfterJump;
};

#endif
