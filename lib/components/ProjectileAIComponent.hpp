#ifndef TEST_AI_COMPONENT_HPP
#define TEST_AI_COMPONENT_HPP

#include "lib/interfaces/IComponent.hpp"
#include "lib/interfaces/IInputComponent.hpp"

class ProjectileAIComponent : public IComponent, public IInputComponent
{
public:
    ProjectileAIComponent();

    virtual ~ProjectileAIComponent() {};

    virtual void update( GameObject& object, sf::Time dt );

    virtual sf::Vector2f getVelocity() const;

    virtual void setVelocity( sf::Vector2f velocity );

private:
    sf::Vector2f mVelocity;
};

#endif
