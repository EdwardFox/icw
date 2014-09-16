#include <cstdint>
#include "lib/components/Box2DPhysicsComponent.hpp"
#include "lib/GameObject.hpp"

Box2DPhysicsComponent::Box2DPhysicsComponent( b2World& physics, GameObject& object, b2BodyType type ) :
        mPhysGroundContactListener()
        , mPhysLeftContactListener()
        , mPhysRightContactListener()
        , mPhysCeilingContactListener()
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

//void Box2DPhysicsComponent::createGroundSensor( b2World& physics, GameObject& object, int tag )
//{
//    mBodyShape.SetAsBox( (object.getSize().x / 2.f - 0.2f) / SCALE, 1.f / SCALE, b2Vec2( 0, ((object.getSize().y / 2.f) / SCALE) ), 0 );
//    mFixtureDef.isSensor = true;
//    mGroundSensorFixture = mBody->CreateFixture( &mFixtureDef );
//    intptr_t tmp = tag;
//    mGroundSensorFixture->SetUserData( ( void* )tmp );
//
//    mPhysGroundContactListener.setTag( tag );
//    physics.SetContactListener( &mPhysGroundContactListener );
//    this->setPhysicsGroundContactListener( &mPhysGroundContactListener );
//}

void Box2DPhysicsComponent::createLeftSensor( b2World& physics, GameObject& object, int tag )
{
    mBodyShape.SetAsBox( 1.f / SCALE, (object.getSize().y / 2.f - 0.2f), b2Vec2( -(object.getSize().y / 2.f) / SCALE, 0 ), 0 );
    mFixtureDef.isSensor = true;
    mLeftSensorFixture = mBody->CreateFixture( &mFixtureDef );
    intptr_t tmp = tag;
    mLeftSensorFixture->SetUserData( ( void* )tmp );

    mPhysLeftContactListener.setTag( tag );
    physics.SetContactListener( &mPhysLeftContactListener );
    this->setPhysicsLeftContactListener( &mPhysLeftContactListener );
}

void Box2DPhysicsComponent::createRightSensor( b2World& physics, GameObject& object, int tag )
{
    mBodyShape.SetAsBox( 1.f / SCALE, (object.getSize().y / 2.f - 0.2f), b2Vec2( (object.getSize().y / 2.f) / SCALE, 0 ), 0 );
    mFixtureDef.isSensor = true;
    mRightSensorFixture = mBody->CreateFixture( &mFixtureDef );
    intptr_t tmp = tag;
    mRightSensorFixture->SetUserData( ( void* )tmp );

    mPhysRightContactListener.setTag( tag );
    physics.SetContactListener( &mPhysRightContactListener );
    this->setPhysicsRightContactListener( &mPhysRightContactListener );
}

void Box2DPhysicsComponent::createCeilingSensor( b2World& physics, GameObject& object, int tag )
{
    mBodyShape.SetAsBox( (object.getSize().x / 2.f - 0.2f) / SCALE, 1.f / SCALE, b2Vec2( 0, -((object.getSize().y / 2.f) / SCALE) ), 0 );
    mFixtureDef.isSensor = true;
    mCeilingSensorFixture = mBody->CreateFixture( &mFixtureDef );
    intptr_t tmp = tag;
    mCeilingSensorFixture->SetUserData( ( void* )tmp );

    mPhysCeilingContactListener.setTag( tag );
    physics.SetContactListener( &mPhysCeilingContactListener );
    this->setPhysicsCeilingContactListener( &mPhysCeilingContactListener );
}

void Box2DPhysicsComponent::setFixedRotation( bool rotation )
{
    mBody->SetFixedRotation( rotation );
}

b2BodyType Box2DPhysicsComponent::getBodyType()
{
    return mBody->GetType();
}

b2Vec2 Box2DPhysicsComponent::getLinearVelocity()
{
    return mBody->GetLinearVelocity();
}

void Box2DPhysicsComponent::setLinearVelocity( b2Vec2 vel )
{
    mBody->SetLinearVelocity( vel );
}

bool Box2DPhysicsComponent::isInAir() const
{
    if( this->getSensor("ground").getListener()->getNumContacts() > 0 )
        return false;
    else
        return true;
}

void Box2DPhysicsComponent::addSensor( std::string key, PhysicsSensor sensor )
{

}

const PhysicsSensor& Box2DPhysicsComponent::getSensor( std::string key ) const
{

}
