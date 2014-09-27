#ifndef TEST_AI_COMPONENT_HPP
#define TEST_AI_COMPONENT_HPP

#include <lib/GameObject.hpp>
#include "lib/interfaces/IComponent.hpp"
#include "lib/interfaces/IInputComponent.hpp"

class ProjectileAIComponent : public IComponent, public IInputComponent
{
public:
    ProjectileAIComponent( GameObject* gameObject );

    virtual ~ProjectileAIComponent() {};

    virtual GameObject* getGameObject() const override;

    virtual void update( GameObject* object, sf::Time dt ) override;

    virtual sf::Vector2f getVelocity() const;

    virtual void setVelocity( sf::Vector2f velocity );
private:
    sf::Vector2f mVelocity;
    GameObject* mGameObject;
};

#endif
