#include <cstdint>
#include "lib/components/Box2DPhysicsComponent.hpp"
#include "lib/GameObject.hpp"

Box2DPhysicsComponent::Box2DPhysicsComponent( b2World& physics, GameObject& object, b2BodyType type ) :
        mPhysContactListener()
{
    this->setType( "PhysicsComponent" );
    createCollisionBody( physics, object, type );
}

void Box2DPhysicsComponent::update( GameObject& object, sf::Time dt )
{
    if ( mBody->GetType() != b2_staticBody )
    {
        object.setPosition( sf::Vector2f( mBody->GetPosition().x * SCALE, mBody->GetPosition().y * SCALE ) );
        object.setRotation( mBody->GetAngle() * 180.f / 3.14f );
    }
}

void Box2DPhysicsComponent::createCollisionBody( b2World& physics, GameObject& object, b2BodyType type )
{
    // Create instances
    mBodyDef = b2BodyDef();
    mBodyShape = b2PolygonShape();
    mFixtureDef = b2FixtureDef();

    // Set type
    mBodyDef.type = type;

    // Set position and create the body
    mBodyDef.position.Set( object.getPosition().x / SCALE, object.getPosition().y / SCALE );
    mBody = physics.CreateBody( &mBodyDef );

    // Box Shape
    mBodyShape.SetAsBox( (object.getSize().x / 2.f) / SCALE, (object.getSize().y / 2.f) / SCALE );

    // Static
    if ( type == b2_staticBody )
    {
        mBody->CreateFixture( &mBodyShape, 0.f );

        // Dynamic or Kinematic
    }
    else
    {
        mFixtureDef.shape = &mBodyShape;
        mFixtureDef.density = 1.f;
        mFixtureDef.friction = 0.0f;
        mBody->CreateFixture( &mFixtureDef );
    }
}

void Box2DPhysicsComponent::createGroundSensor( b2World& physics, GameObject& object, int tag )
{
    mBodyShape.SetAsBox( (object.getSize().x / 2.f - 1.f) / SCALE, 1.f / SCALE, b2Vec2( 0, ((object.getSize().y / 2.f) / SCALE) ), 0 );
    mFixtureDef.isSensor = true;
    mGroundSensorFixture = mBody->CreateFixture( &mFixtureDef );
    intptr_t tmp = tag;
    mGroundSensorFixture->SetUserData( ( void* )tmp );

    physics.SetContactListener( &mPhysContactListener );
    this->setPhysicsGroundContactListener( &mPhysContactListener );
}

void Box2DPhysicsComponent::setFixedRotation( bool rotation )
{
    mBody->SetFixedRotation( rotation );
}
