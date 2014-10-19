#ifndef SPAWNER_COMPONENT_HPP
#define SPAWNER_COMPONENT_HPP

#include <unordered_map>
#include "lib/interfaces/IComponent.hpp"
#include "lib/interfaces/ISpawnerComponent.hpp"

class SpawnerComponent : public IComponent, public ISpawnerComponent
{
public:
    SpawnerComponent( GameObject* gameObject );

    virtual ~SpawnerComponent() {};

    virtual GameObject* getGameObject() const override;

    virtual void update( GameObject* object, sf::Time dt ) override;

    virtual void spawn();

private:
    GameObject* mGameObject;
    sf::Clock mTimer;
    unsigned mRandomTime;
};

#endif

