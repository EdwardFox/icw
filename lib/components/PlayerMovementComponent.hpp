#ifndef PLAYER_MOVEMENT_COMPONENT_HPP
#define PLAYER_MOVEMENT_COMPONENT_HPP

#include "lib/interfaces/IComponent.hpp"
#include "lib/interfaces/IMovementComponent.hpp"

class PlayerMovementComponent : public IComponent, public IMovementComponent
{
public:
    PlayerMovementComponent();

    virtual void move( GameObject& object, Movement mov );

    virtual void jump( GameObject& object );

    virtual void wallJump( GameObject& object );

    virtual void update( GameObject& object, sf::Time dt );

    virtual float getMoveSpeed() const;

    virtual void setMoveSpeed( float movespeed );

    virtual float getJumpHeight() const;

    virtual void setJumpHeight( float jumpheight );

    virtual int getDelayThresholdAfterJump() const;

    virtual void setDelayThresholdAfterJump( float delay );

    virtual int getCurrentDelayAfterJump() const;

    virtual void setCurrentDelayAfterJump( float delay );

private:
    float mMoveSpeed;
    float mJumpHeight;
    float mWallBounceStrength;
    int mDelayThresholdAfterJump;
    int mCurrentDelayAfterJump;
    int mDelayThresholdAfterWallJump;
    sf::Clock mCurrentDelayAfterWallJump;
};

#endif
