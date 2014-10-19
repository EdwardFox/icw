#ifndef PHYSICS_GROUND_CONTACT_LISTENER_HPP
#define PHYSICS_GROUND_CONTACT_LISTENER_HPP

#include <Box2D/Box2D.h>

class PhysicsContactListener : public b2ContactListener
{
public:
    PhysicsContactListener();

    virtual void BeginContact( b2Contact* contact );

    virtual void EndContact( b2Contact* contact );

    virtual void PreSolve( b2Contact* contact, const b2Manifold* oldManifold ) override;

    virtual void PostSolve( b2Contact* contact, const b2ContactImpulse* impulse ) override;
};

#endif