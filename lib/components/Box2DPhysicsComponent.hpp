#ifndef DEFAULT_PHYSICS_COMPONENT_HPP
#define DEFAULT_PHYSICS_COMPONENT_HPP

#include <memory>
#include <string>
#include <unordered_map>
#include "lib/interfaces/IComponent.hpp"
#include "lib/interfaces/IPhysicsComponent.hpp"
#include "lib/PhysicsContactListener.hpp"
#include "lib/PhysicsSensor.hpp"

//class Box2DPhysicsComponent : public IComponent, public IPhysicsComponent//public IContactable, public IComponent, public IPhysicsComponent
//class Box2DPhysicsComponent : public IContactable, public IComponent, public IPhysicsComponent
class Box2DPhysicsComponent : public IComponent, public IPhysicsComponent, public IContactable
{
public:
    Box2DPhysicsComponent( b2World& physics, GameObject& object, b2BodyType type );

    virtual ~Box2DPhysicsComponent() {};

    virtual void update( GameObject& object, sf::Time dt );

    virtual void createCollisionBody( b2World& physics, GameObject& object, b2BodyType type );

    virtual void setFixedRotation( bool rotation );

    virtual b2BodyType getBodyType();

    virtual b2Vec2 getLinearVelocity();

    virtual void setLinearVelocity( b2Vec2 vel );

    virtual void addLinearImpulse( b2Vec2 impulse );

    virtual void setFriction( float friction );

    virtual bool isInAir() const;

    virtual Collision hitWall() const;

    virtual void addSensor( std::string key, b2World& physics, b2Vec2 size, b2Vec2 position );

    virtual const PhysicsSensor* getSensor( std::string key ) const;

    virtual float getGravityScale() const;

    virtual void setGravityScale( float gravityScale );

    virtual void createDefaultSensors( b2World& physics, GameObject& object );

    virtual void onContact( Contact contact );

    virtual void onContact( Contact contact, IContactable* other );

    virtual void setContactable( bool contactable );

private:

    std::unordered_map<std::string, std::unique_ptr<PhysicsSensor>> mSensors;

    b2BodyDef mBodyDef;
    b2Body* mBody;
    b2PolygonShape mPolygonShape;
    b2ChainShape mChainShape[4];
    b2FixtureDef mFixtureDef;
};

#endif
