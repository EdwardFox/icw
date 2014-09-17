#ifndef PHYSICS_GROUND_CONTACT_LISTENER_HPP
#define PHYSICS_GROUND_CONTACT_LISTENER_HPP

#include <Box2D/Box2D.h>

class PhysicsContactListener : public b2ContactListener
{
public:
    PhysicsContactListener();

    void BeginContact( b2Contact* contact );

    void EndContact( b2Contact* contact );

};

#endif