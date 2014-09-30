#ifndef TEST_AI_COMPONENT_HPP
#define TEST_AI_COMPONENT_HPP

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

private:
    GameObject* mGameObject;
};

#endif
