#ifndef DEFAULT_PHYSICS_COMPONENT_HPP
#define DEFAULT_PHYSICS_COMPONENT_HPP

#include <memory>
#include <string>
#include <unordered_map>
#include <lib/GameObject.hpp>
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

    virtual ~Box2DPhysicsComponent();

    virtual GameObject* getGameObject() const override;

    virtual void update( GameObject& object, sf::Time dt ) override;

    virtual void createCollisionBody( b2World& physics, GameObject& object, b2BodyType type ) override;

    virtual void setFixedRotation( bool rotation ) override;

    virtual b2BodyType getBodyType() override;

    virtual b2Vec2 getLinearVelocity() override;

    virtual void setLinearVelocity( b2Vec2 vel ) override;

    virtual void addLinearImpulse( b2Vec2 impulse ) override;

    virtual void setFriction( float friction ) override;

    virtual bool isInAir() const override;

    virtual Collision hitWall() const override;

    virtual void addSensor( std::string key, b2World& physics, b2Vec2 size, b2Vec2 position ) override;

    virtual const PhysicsSensor* getSensor( std::string key ) const override;

    virtual float getGravityScale() const override;

    virtual void setGravityScale( float gravityScale ) override;

    virtual void createDefaultSensors( b2World& physics, GameObject& object );

    virtual void onContact( Contact contact ) override;

    virtual void onContact( Contact contact, IContactable* other ) override;

    virtual void setContactable( bool contactable );

    virtual void destroyBody() override;

private:

    std::unordered_map<std::string, std::unique_ptr<PhysicsSensor>> mSensors;
    GameObject* mGameObject;
    b2BodyDef mBodyDef;
    b2Body* mBody;
    b2PolygonShape mPolygonShape;
    b2ChainShape mChainShape[4];
    b2FixtureDef mFixtureDef;
};

#endif
