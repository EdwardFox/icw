#include <cstdint>
#include "lib/components/Box2DPhysicsComponent.hpp"
#include "lib/GameObject.hpp"

Box2DPhysicsComponent::Box2DPhysicsComponent( b2World& physics, GameObject& object, b2BodyType type, int& tag ) :
        mSensors()
        , mBodyDef()
        , mBody( nullptr )
        , mBodyShape()
        , mFixtureDef()
        , mListener( nullptr )
        , mGroundTag( 0 )
        , mCeilingTag( 0 )
        , mLeftTag( 0 )
        , mRightTag( 0 )
{
    this->setType( "PhysicsComponent" );
    createCollisionBody( physics, object, type );

    if ( type != b2_staticBody )
    {
        this->createDefaultSensors( physics, object, tag );
    }
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
    if ( mListener->getNumContacts( mGroundTag ) > 0 )
        return false;
    else
        return true;
}

Collision Box2DPhysicsComponent::hitWall() const
{
    if ( mListener->getNumContacts( mLeftTag ) > 0 )
        return Collision::Left;
    else if ( mListener->getNumContacts( mRightTag ) > 0 )
        return Collision::Right;
    else
        return Collision::None;

}

void Box2DPhysicsComponent::addSensor( std::string key, b2World& physics, b2Vec2 size, b2Vec2 position, int tag )
{
    PhysicsSensor* sensor = new PhysicsSensor();
    sensor->createSensor( physics, mBody, size, position, tag );

    mSensors.emplace( key, std::unique_ptr<PhysicsSensor>( sensor ) );
}

const PhysicsSensor* Box2DPhysicsComponent::getSensor( std::string key ) const
{
    try
    {
        return mSensors.at( key ).get();
    }
    catch ( std::out_of_range oor )
    {
        return nullptr;
    }
}

void Box2DPhysicsComponent::setListener( PhysicsContactListener* listener )
{
    mListener = listener;
}

void Box2DPhysicsComponent::createDefaultSensors( b2World& physics, GameObject& object, int& tag )
{
    mGroundTag = tag;
    this->addSensor( "ground", physics, b2Vec2( (object.getSize().x / 2.f - 0.2f) / SCALE, 1.f / SCALE ), b2Vec2( 0, ((object.getSize().y / 2.f) / SCALE) ), tag++ );
    mCeilingTag = tag;
    this->addSensor( "ceiling", physics, b2Vec2( (object.getSize().x / 2.f - 0.2f) / SCALE, 1.f / SCALE ), b2Vec2( 0, -((object.getSize().y / 2.f) / SCALE) ), tag++ );
    mLeftTag = tag;
    this->addSensor( "left", physics, b2Vec2( 1.f / SCALE, (object.getSize().y / 2.f - 0.2f) / SCALE ), b2Vec2( -(object.getSize().y / 2.f) / SCALE, 0 ), tag++ );
    mRightTag = tag;
    this->addSensor( "right", physics, b2Vec2( 1.f / SCALE, (object.getSize().y / 2.f - 0.2f) / SCALE ), b2Vec2( (object.getSize().y / 2.f) / SCALE, 0 ), tag++ );
}
