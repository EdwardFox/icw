#ifndef PHYSICS_SENSOR_HPP
#define PHYSICS_SENSOR_HPP

#include <Box2D/Box2D.h>

class PhysicsSensor
{
public:
    PhysicsSensor();

    void createSensor( b2World& physics, b2Body* body, b2Vec2 size, b2Vec2 position, int tag);

private:
    b2PolygonShape mSensorShape;
    b2FixtureDef mFixtureDef;
    b2Fixture* mSensorFixture;
};

#endif