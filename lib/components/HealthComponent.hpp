#ifndef HEALTH_COMPONENT_HPP
#define HEALTH_COMPONENT_HPP

#include <unordered_map>
#include "lib/interfaces/IComponent.hpp"
#include "lib/interfaces/IHealthComponent.hpp"

class HealthComponent : public IComponent, public IHealthComponent
{
public:
    HealthComponent( GameObject* gameObject );

    virtual ~HealthComponent()
    {
    };

    virtual GameObject* getGameObject() const override;

    virtual void update( GameObject* object, sf::Time dt ) override;

    virtual float getHealth() const override;

    virtual float getMaximumHealth() const override;

    virtual void receiveDamage( std::string element, float damage ) override;

    virtual void addDamageResponse( std::string element, std::function<void( std::string, float )> function ) override;

protected:
    virtual void setHealth( float health ) override;

    virtual void setMaximumHealth( float health ) override;

private:
    std::unordered_map<std::string, std::function<void( std::string, float )>> mResponses;
    GameObject* mGameObject;
    float mMaxHealth;
    float mHealth;

};

#endif

