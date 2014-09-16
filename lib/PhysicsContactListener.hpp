#ifndef PHYSICS_GROUND_CONTACT_LISTENER_HPP
#define PHYSICS_GROUND_CONTACT_LISTENER_HPP

#include <Box2D/Box2D.h>
#include <unordered_map>

class PhysicsContactListener : public b2ContactListener
{
public:
    PhysicsContactListener();

    void BeginContact( b2Contact* contact );

    void EndContact( b2Contact* contact );

    int getNumContacts( int tag ) const;

    bool tagExists( int tag ) const;

private:
    std::unordered_map<int, int> mContacts;
};

#endif