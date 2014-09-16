#ifndef IPHYSICS_COMPONENT_HPP
#define IPHYSICS_COMPONENT_HPP

#include <Box2D/Box2D.h>
#include <string>
#include "lib/Data.hpp"

class GameObject;

class PhysicsSensor;

class IPhysicsComponent
{
public:
    virtual void createCollisionBody( b2World& physics, GameObject& object, b2BodyType type ) = 0;

    virtual void setFixedRotation( bool rotation ) = 0;

    virtual b2BodyType getBodyType() = 0;

    virtual b2Vec2 getLinearVelocity() = 0;

    virtual void setLinearVelocity( b2Vec2 vel ) = 0;

    virtual bool isInAir() const = 0;

    virtual Collision hitWall() const = 0;

    virtual void addSensor( std::string key, b2World& physics, b2Vec2 size, b2Vec2 position, int tag ) = 0;

    virtual const PhysicsSensor* getSensor( std::string key ) const = 0;

};

#endif
