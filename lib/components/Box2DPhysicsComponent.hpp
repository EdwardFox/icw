#ifndef DEFAULT_PHYSICS_COMPONENT_HPP
#define DEFAULT_PHYSICS_COMPONENT_HPP

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <lib/GameObject.hpp>
#include "lib/interfaces/IComponent.hpp"
#include "lib/interfaces/IPhysicsComponent.hpp"
#include "lib/PhysicsContactListener.hpp"
#include "lib/PhysicsSensor.hpp"

/**
* PhysicsComponent implementation for the Box2D library.
* Handles physics interactions of the game object as well as
* collision callbacks.
*/
class Box2DPhysicsComponent : public IComponent, public IPhysicsComponent, public IContactable
{
public:
    /**
    * Automatically creates the collision body on initialization
    */
    Box2DPhysicsComponent( b2World* physics, GameObject* object, b2BodyType type );

    /**
    * Destructor
    */
    virtual ~Box2DPhysicsComponent();

    /**
    * Access the game object this component is attached to
    */
    virtual GameObject* getGameObject() const override
    {
        return mGameObject;
    }

    /**
    * Updates the attributes and position of (movable) bodies
    */
    virtual void update( GameObject* object, sf::Time dt ) override;

    /**
    * Creates the default collision body.
    * Box Shape for dynamic bodies, ChainShapes for static and kinematic bodies
    * to guarantee smooth movement for movable game objects along the edges of the
    * body.
    */
    virtual void createCollisionBody( b2World* physics, GameObject* object, b2BodyType type ) override;

    /**
    * Enable or disable rotation for the body
    */
    virtual void setFixedRotation( bool rotation ) override
    {
        mBody->SetFixedRotation( rotation );
    }

    /**
    * Returns the b2_bodytype
    * TODO: Make the return type of the implemented contract independent of the Box2D library
    */
    virtual b2BodyType getBodyType() override
    {
        return mBody->GetType();
    }

    /**
    * Returns the linear velocity of the body
    */
    virtual b2Vec2 getLinearVelocity() override
    {
        return mBody->GetLinearVelocity();
    }

    /**
    * Sets the linear velocity of the body
    */
    virtual void setLinearVelocity( b2Vec2 vel ) override
    {
        mBody->SetLinearVelocity( vel );
    }

    /**
    * Adds a linear impulse to the body at its center
    */
    virtual void addLinearImpulse( b2Vec2 impulse ) override
    {
        mBody->ApplyLinearImpulse( impulse, mBody->GetWorldCenter(), true );
    }

    /**
    * Sets the friction for each fixture
    */
    virtual void setFriction( float friction ) override
    {
        for ( b2Fixture* f = mBody->GetFixtureList(); f; f = f->GetNext() )
        {
            f->SetFriction( friction );
        }
    }

    /**
    * Checks whether the body is in the air.
    * Note: This method works only if the default sensors have been created
    */
    virtual bool isInAir() const override;

    /**
    * Checks whether the body has hit a wall on either side (left/right)
    * Note: This method works only if the default sensors have been created
    */
    virtual Collision hitWall() const override;

    /**
    * Adds a sensor to the body
    *
    * std::string key   - Identifier for the sensor
    * b2World& physics  - Reference to the physics world
    * b2Vec2 size       - Half-size of the sensor
    * b2Vec2            - Centered position of the sensor relative to the body
    *
    * TODO: Make the physics world, sensor size and position independent from the Box2D library
    */
    virtual void addSensor( std::string key, b2World* physics, b2Vec2 size, b2Vec2 position ) override;

    /**
    * Returns a pointer to a sensor by key, or nullptr if it does not exist
    */
    virtual const PhysicsSensor* getSensor( std::string key ) const override;

    /**
    * Returns the gravity scale of this body
    */
    virtual float getGravityScale() const override
    {
        return mBody->GetGravityScale();
    }

    /**
    * Sets the gravity scale for this body
    */
    virtual void setGravityScale( float gravityScale ) override
    {
        mBody->SetGravityScale( gravityScale );
    }

    /**
    * Helper function to create default sensor for top, bottom, left and right of the game object.
    * Enables the isInAir() and hitWall() functions
    */
    virtual void createDefaultSensors( b2World* physics, GameObject* object );

    /**
    * Implements the onContact method declared by the IContactable interface.
    * This method is called when colliding with a body that implements the
    * IContactable interface
    *
    * Contact contact       - The type of the contact, e.g. Begin / End
    * IContactable* other   - The other contactable we collided with. This will
    *                         most likely be another game object that has a box2d component attached.
    */
    virtual void onContact( Contact contact, IContactable* other ) override;

    /**
    * Sets whether is component can be listened to via the customized contact listener
    */
    virtual void setContactable( bool contactable );

    /**
    * Destroys the physical body of this PhysicsComponent.
    * Intended to be used right before destroying the game object.
    * Use with care.
    */
    virtual void destroyBody() override;

private:

    /**
    * Holds the key - value pairs for the sensors
    */
    std::unordered_map<std::string, std::unique_ptr<PhysicsSensor>> mSensors;

    /**
    * Holds a pointer to the game object
    */
    GameObject* mGameObject;

    /**
    * Holds the Box2D body definition
    */
    b2BodyDef mBodyDef;

    /**
    * Holds a pointer to the Box2D body
    */
    b2Body* mBody;

    /**
    * Holds the Box2D polygon shape for kinematic and dynamic bodies
    */
    b2PolygonShape mPolygonShape;

    /**
    * Holds the Box2D chainshape for static bodies
    */
    b2ChainShape mChainShape[4];

    /**
    * Holds the Box2D fixture definition
    */
    b2FixtureDef mFixtureDef;

};

#endif
