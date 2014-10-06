#ifndef TEST_AI_COMPONENT_HPP
#define TEST_AI_COMPONENT_HPP

#include <lib/gameobjects/GameObject.hpp>
#include "lib/interfaces/IComponent.hpp"
#include "lib/interfaces/IInputComponent.hpp"

class EnemyAIComponent : public IComponent, public IInputComponent
{
public:
    EnemyAIComponent( GameObject* gameObject );

    virtual ~EnemyAIComponent() {};

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
    int mRunLeft;
};

#endif
