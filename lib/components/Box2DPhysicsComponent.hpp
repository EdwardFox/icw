#ifndef DEFAULT_PHYSICS_COMPONENT_HPP
#define DEFAULT_PHYSICS_COMPONENT_HPP

#include <memory>
#include <string>
#include <unordered_map>
#include "lib/interfaces/IComponent.hpp"
#include "lib/interfaces/IPhysicsComponent.hpp"
#include "lib/PhysicsContactListener.hpp"
#include "lib/PhysicsSensor.hpp"

class Box2DPhysicsComponent : public IComponent, public IPhysicsComponent
{
public:
    Box2DPhysicsComponent( b2World& physics, GameObject& object, b2BodyType type, int& tag );

    virtual void update( GameObject& object, sf::Time dt );

    virtual void createCollisionBody( b2World& physics, GameObject& object, b2BodyType type );

    virtual void setFixedRotation( bool rotation );

    virtual b2BodyType getBodyType();

    virtual b2Vec2 getLinearVelocity();

    virtual void setLinearVelocity( b2Vec2 vel );

    virtual bool isInAir() const;

    virtual Collision hitWall() const;

    virtual void addSensor( std::string key, b2World& physics, b2Vec2 size, b2Vec2 position, int tag );

    virtual const PhysicsSensor* getSensor( std::string key ) const;

    virtual void setListener( PhysicsContactListener* listener );

private:
    void createDefaultSensors( b2World& physics, GameObject& object, int& tag );

    std::unordered_map<std::string, std::unique_ptr<PhysicsSensor>> mSensors;

    b2BodyDef mBodyDef;
    b2Body* mBody;
    b2PolygonShape mBodyShape;
    b2FixtureDef mFixtureDef;

    PhysicsContactListener* mListener;
    int mGroundTag;
    int mCeilingTag;
    int mLeftTag;
    int mRightTag;
};

#endif
