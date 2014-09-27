#ifndef PLAYER_MOVEMENT_COMPONENT_HPP
#define PLAYER_MOVEMENT_COMPONENT_HPP

#include "lib/interfaces/IComponent.hpp"
#include "lib/interfaces/IMovementComponent.hpp"

class PlayerMovementComponent : public IComponent, public IMovementComponent
{
public:
    PlayerMovementComponent( GameObject* gameObject );

    virtual ~PlayerMovementComponent()
    {
    };

    virtual GameObject* getGameObject() const override;

    virtual void move( GameObject* object, Movement mov ) override;

    virtual void jump( GameObject* object ) override;

    virtual void update( GameObject* object, sf::Time dt ) override;

    virtual float getMoveSpeed() const override;

    virtual void setMoveSpeed( float movespeed ) override;

    virtual float getAcceleration() const override;

    virtual void setAcceleration( float accel ) override;

    virtual float getFriction() const override;

    virtual void setFriction( float friction ) override;

    virtual float getJumpHeight() const override;

    virtual void setJumpHeight( float jumpheight ) override;

    virtual int getDelayThresholdAfterJump() const override;

    virtual void setDelayThresholdAfterJump( float delay ) override;

    virtual int getCurrentDelayAfterJump() const override;

    virtual void setCurrentDelayAfterJump( float delay ) override;

private:
    float mMoveSpeed;
    GameObject* mGameObject;
    float mAcceleration;
    float mFriction;
    float mJumpHeight;
    float mWallBounceStrength;
    int mDelayThresholdAfterJump;
    int mCurrentDelayAfterJump;
};

#endif
