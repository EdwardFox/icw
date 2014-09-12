#ifndef IPHYSICS_COMPONENT_HPP
#define IPHYSICS_COMPONENT_HPP

#include <Box2D/Box2D.h>
#include "lib/PhysicsGroundContactListener.hpp"

class GameObject;

//class PhysicsGroundContactListener;

class IPhysicsComponent
{
public:
    virtual void createCollisionBody( b2World& physics, GameObject& object, b2BodyType type ) = 0;

    virtual void createGroundSensor( b2World& physics, GameObject& object, int tag ) = 0;

    virtual void setFixedRotation( bool rotation ) = 0;

    b2BodyType getBodyType()
    {
        return mBody->GetType();
    }

    b2Vec2 getLinearVelocity()
    {
        return mBody->GetLinearVelocity();
    }

    void setLinearVelocity( b2Vec2 vel )
    {
        mBody->SetLinearVelocity( vel );
    }

    void setPhysicsGroundContactListener( PhysicsGroundContactListener* physCL )
    {
        mPhysicsGroundContactListener = physCL;
    }

    PhysicsGroundContactListener* getPhysicsGroundContactListener() const
    {
        return mPhysicsGroundContactListener;
    }

    int getTag() const
    {
        return mPhysicsGroundContactListener->getTag();
    }

    void setTag( int tag )
    {
        mPhysicsGroundContactListener->setTag( tag );
    }

protected:
    b2BodyDef mBodyDef;
    b2Body* mBody;
    b2PolygonShape mBodyShape;
    b2FixtureDef mFixtureDef;
    b2Fixture* mGroundSensorFixture;
    PhysicsGroundContactListener* mPhysicsGroundContactListener;
};

#endif
