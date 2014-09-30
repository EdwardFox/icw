#ifndef PROJECTILE_MOVEMENT_COMPONENT
#define PROJECTILE_MOVEMENT_COMPONENT

#include <lib/interfaces/IProjectileMovementComponent.hpp>
#include <lib/gameobjects/GameObject.hpp>

class ProjectileMovementComponent : public IComponent, public IProjectileMovementComponent
{

public:

    ProjectileMovementComponent( GameObject* object );

    virtual ~ProjectileMovementComponent()
    {
    };

    virtual void update( GameObject* object, sf::Time dt ) override;

    virtual void move( GameObject* object ) override;

    virtual GameObject* getGameObject() const override
    {
        return mGameObject;
    }

    sf::Vector2f getMoveSpeed() const override
    {
        return mMovementSpeed;
    }

    void setMoveSpeed( sf::Vector2f movespeed ) override
    {
        mMovementSpeed = movespeed;
    }


private:
    GameObject* mGameObject;
    sf::Vector2f mMovementSpeed;
};

#endif