#ifndef DEFAULT_PHYSICS_COMPONENT_HPP
#define DEFAULT_PHYSICS_COMPONENT_HPP

#include "lib/interfaces/IComponent.hpp"
#include "lib/interfaces/IPhysicsComponent.hpp"

class Box2DPhysicsComponent : public IComponent, public IPhysicsComponent
{
    public:
        Box2DPhysicsComponent(b2World& physics, GameObject& object, b2BodyType type);

        virtual void update(GameObject& object, sf::Time dt);
        virtual void createCollisionBody(b2World& physics, GameObject& object, b2BodyType type);
};

#endif
