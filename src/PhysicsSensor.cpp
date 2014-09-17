#include "lib/PhysicsSensor.hpp"

PhysicsSensor::PhysicsSensor() :
        mSensorShape()
        , mFixtureDef()
        , mSensorFixture( nullptr )
        , mContacts( 0 )
{

}

void PhysicsSensor::createSensor( b2World& physics, b2Body* body, b2Vec2 size, b2Vec2 position )
{
    mFixtureDef.shape = &mSensorShape;
    mFixtureDef.density = 1.f;
    mFixtureDef.friction = 0.f;
    mFixtureDef.isSensor = true;

    mSensorShape.SetAsBox( size.x, size.y, position, 0 );
    mSensorFixture = body->CreateFixture( &mFixtureDef );
    mSensorFixture->SetUserData( ( void* )this );
}

void PhysicsSensor::setFriction( float friction )
{
    mFixtureDef.friction = friction;
}

void PhysicsSensor::onContact( Contact contact )
{
    if( Contact::Begin == contact )
        mContacts++;
    else if( Contact::End == contact )
        mContacts--;
}

int PhysicsSensor::getContacts() const
{
    return mContacts;
}

void PhysicsSensor::setContacts( int contact )
{
    mContacts = contact;
}
