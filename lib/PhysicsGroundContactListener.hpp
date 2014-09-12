#ifndef PHYSICS_GROUND_CONTACT_LISTENER_HPP
#define PHYSICS_GROUND_CONTACT_LISTENER_HPP

#include <Box2D/Box2D.h>

class PhysicsGroundContactListener : public b2ContactListener
{
public:
    PhysicsGroundContactListener();

    void BeginContact( b2Contact* contact );

    void EndContact( b2Contact* contact );

    int getNumGroundContacts() const;

    int getTag() const
    {
        return mTag;
    }

    void setTag( int tag )
    {
        mTag = tag;
    }


private:
    int mNumGroundContacts;
    int mTag;
};

#endif