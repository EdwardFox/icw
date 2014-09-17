#ifndef PHYSICS_SENSOR_HPP
#define PHYSICS_SENSOR_HPP

#include <Box2D/Box2D.h>
#include "lib/interfaces/IContactable.hpp"

class PhysicsSensor : IContactable
{
public:
    PhysicsSensor();

    void createSensor( b2World& physics, b2Body* body, b2Vec2 size, b2Vec2 position );

    void setFriction( float friction );

    virtual void onContact( Contact contact );

    int getContacts() const;

    void setContacts( int contact );

private:
    b2PolygonShape mSensorShape;
    b2FixtureDef mFixtureDef;
    b2Fixture* mSensorFixture;
    int mContacts;
};

#endif