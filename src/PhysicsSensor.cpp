#include "lib/PhysicsSensor.hpp"
#include <cstdint>

PhysicsSensor::PhysicsSensor() :
        mSensorShape()
        , mFixtureDef()
        , mSensorFixture( nullptr )
{

}

void PhysicsSensor::createSensor( b2World& physics, b2Body* body, b2Vec2 size, b2Vec2 position, int tag )
{
    mFixtureDef.shape = &mSensorShape;
    mFixtureDef.density = 1.f;
    mFixtureDef.friction = 0.f;
    mFixtureDef.isSensor = true;

    mSensorShape.SetAsBox( size.x, size.y, position, 0 );
    mSensorFixture = body->CreateFixture( &mFixtureDef );
    intptr_t tmp = tag;
    mSensorFixture->SetUserData( ( void* )tmp );
}
