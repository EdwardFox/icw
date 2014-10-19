#ifndef PROJECTILE_AI_COMPONENT
#define PROJECTILE_AI_COMPONENT

#include <lib/gameobjects/GameObject.hpp>
#include "lib/interfaces/IComponent.hpp"
#include "lib/interfaces/IInputComponent.hpp"

class ProjectileAIComponent : public IComponent, public IInputComponent
{
public:
    ProjectileAIComponent( GameObject* gameObject );

    virtual ~ProjectileAIComponent() {};

    virtual void update( GameObject* object, sf::Time dt ) override;

    virtual GameObject* getGameObject() const override
    {
        return mGameObject;
    }

    int getTimeAlive() const
    {
        return mTimeAlive;
    }

    void setTimeAlive( int timeAlive )
    {
        mTimeAlive = timeAlive;
    }

    int getMaxTimeAlive() const
    {
        return mMaxTimeAlive;
    }

    void setMaxTimeAlive( int maxTimeAlive )
    {
        mMaxTimeAlive = maxTimeAlive;
    }

private:
    GameObject* mGameObject;
    int mTimeAlive;
    int mMaxTimeAlive;
};

#endif
