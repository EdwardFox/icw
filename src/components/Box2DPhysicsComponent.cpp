#include <cstdint>
#include "lib/components/Box2DPhysicsComponent.hpp"

Box2DPhysicsComponent::Box2DPhysicsComponent( b2World* physics, GameObject* object, b2BodyType type ) :
        mSensors()
        , mGameObject( object )
        , mBodyDef()
        , mBody( nullptr )
        , mPolygonShape()
        , mChainShape()
        , mFixtureDef()
{
    this->setType( "PhysicsComponent" );
    createCollisionBody( physics, object, type );
}

Box2DPhysicsComponent::~Box2DPhysicsComponent()
{
}

void Box2DPhysicsComponent::update( GameObject* object, sf::Time dt )
{
    if ( mBody->GetType() != b2_staticBody )
    {
        object->setPosition( sf::Vector2f( mBody->GetPosition().x * SCALE, mBody->GetPosition().y * SCALE ) );
        object->setRotation( mBody->GetAngle() * 180.f / 3.14f );
    }
}

void Box2DPhysicsComponent::createCollisionBody( b2World* physics, GameObject* object, b2BodyType type )
{
    // Create instances
    mBodyDef = b2BodyDef();
    mPolygonShape = b2PolygonShape();
    mFixtureDef = b2FixtureDef();

    // Set type
    mBodyDef.type = type;

    // Set position and create the body
    mBodyDef.position.Set( object->getPosition().x / SCALE, object->getPosition().y / SCALE );
    mBody = physics->CreateBody( &mBodyDef );

    /*
    *   SHAPE
    *
    *   Dynamic bodies get a standard polygon box shape.
    *
    *   Static and kinematic bodies get a a rectangular shape made of
    *   egde chains (one per side; so four total) to fix the ghost vertices
    *   problem. This is done by defining previous and next vertices that
    *   Box2D can use in its calculation.
    *
    *   More info:
    *       http://www.box2d.org/manual.html#_Toc258082970
    *       http://www.iforce2d.net/b2dtut/ghost-vertices
    *
    */
    if ( type != b2_dynamicBody )
    {
        // Top
        b2Vec2 vs[2];
        vs[0].Set( (-object->getSize().x / 2.f) / SCALE, -object->getSize().y / 2.f / SCALE );
        vs[1].Set( (object->getSize().x / 2.f) / SCALE, -object->getSize().y / 2.f / SCALE );
        mChainShape[0].CreateChain( vs, 2 );
        mChainShape[0].SetPrevVertex( b2Vec2( (-object->getSize().x - object->getSize().x / 2.f) / SCALE, object->getSize().y / 2.f / SCALE ) );
        mChainShape[0].SetNextVertex( b2Vec2( (object->getSize().x + object->getSize().x / 2.f) / SCALE, object->getSize().y / 2.f / SCALE ) );
        mBody->CreateFixture( &mChainShape[0], 0.f );

        // Bottom
        vs[0].Set( (-object->getSize().x / 2.f) / SCALE, object->getSize().y / 2.f / SCALE );
        vs[1].Set( (object->getSize().x / 2.f) / SCALE, object->getSize().y / 2.f / SCALE );
        mChainShape[1].CreateChain( vs, 2 );
        mChainShape[1].SetPrevVertex( b2Vec2( (-object->getSize().x - object->getSize().x / 2.f) / SCALE, object->getSize().y / 2.f / SCALE ) );
        mChainShape[1].SetNextVertex( b2Vec2( (object->getSize().x + object->getSize().x / 2.f) / SCALE, object->getSize().y / 2.f / SCALE ) );
        mBody->CreateFixture( &mChainShape[1], 0.f );

        // Left
        vs[0].Set( (-object->getSize().x / 2.f) / SCALE, -object->getSize().y / 2.f / SCALE );
        vs[1].Set( (-object->getSize().x / 2.f) / SCALE, object->getSize().y / 2.f / SCALE );
        mChainShape[2].CreateChain( vs, 2 );
        mChainShape[2].SetPrevVertex( b2Vec2( -object->getSize().x / 2.f / SCALE, (-object->getSize().y - object->getSize().y / 2.f) / SCALE ) );
        mChainShape[2].SetNextVertex( b2Vec2( -object->getSize().x / 2.f / SCALE, (object->getSize().y + object->getSize().y / 2.f) / SCALE ) );
        mBody->CreateFixture( &mChainShape[2], 0.f );

        // Right
        vs[0].Set( (object->getSize().x / 2.f) / SCALE, -object->getSize().y / 2.f / SCALE );
        vs[1].Set( (object->getSize().x / 2.f) / SCALE, object->getSize().y / 2.f / SCALE );
        mChainShape[3].CreateChain( vs, 2 );
        mChainShape[3].SetPrevVertex( b2Vec2( object->getSize().x / 2.f / SCALE, (-object->getSize().y - object->getSize().y / 2.f) / SCALE ) );
        mChainShape[3].SetNextVertex( b2Vec2( object->getSize().x / 2.f / SCALE, (object->getSize().y + object->getSize().y / 2.f) / SCALE ) );
        mBody->CreateFixture( &mChainShape[3], 0.f );
    }
    else
    {
        mPolygonShape.SetAsBox( (object->getSize().x / 2.f) / SCALE, (object->getSize().y / 2.f) / SCALE );
        mFixtureDef.shape = &mPolygonShape;
        mFixtureDef.density = 1.f;
        mFixtureDef.friction = 1.0f;
        mBody->CreateFixture( &mFixtureDef );
    }
}

bool Box2DPhysicsComponent::isInAir() const
{
    if ( this->getSensor( "ground" )->getContacts() > 0 )
        return false;
    else
        return true;
}

Collision Box2DPhysicsComponent::hitWall() const
{
    if ( this->getSensor( "left" )->getContacts() > 0 )
        return Collision::Left;
    else if ( this->getSensor( "right" )->getContacts() > 0 )
        return Collision::Right;
    else
        return Collision::None;

}

void Box2DPhysicsComponent::addSensor( std::string key, b2World* physics, b2Vec2 size, b2Vec2 position )
{
    PhysicsSensor* sensor = new PhysicsSensor();
    sensor->createSensor( physics, mBody, size, position );

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

void Box2DPhysicsComponent::createDefaultSensors( b2World* physics, GameObject* object )
{
    this->addSensor( "ground", physics, b2Vec2( (object->getSize().x / 2.f - 2.f) / SCALE, 1.f / SCALE ), b2Vec2( 0, ((object->getSize().y / 2.f) / SCALE) ) );
    this->addSensor( "ceiling", physics, b2Vec2( (object->getSize().x / 2.f - 2.f) / SCALE, 1.f / SCALE ), b2Vec2( 0, -((object->getSize().y / 2.f) / SCALE) ) );
    this->addSensor( "left", physics, b2Vec2( 1.f / SCALE, (object->getSize().y / 2.f - 2.f) / SCALE ), b2Vec2( -(object->getSize().y / 2.f) / SCALE, 0 ) );
    this->addSensor( "right", physics, b2Vec2( 1.f / SCALE, (object->getSize().y / 2.f - 2.f) / SCALE ), b2Vec2( (object->getSize().y / 2.f) / SCALE, 0 ) );
}

void Box2DPhysicsComponent::onContact( Contact contact, IContactable* other )
{
    if ( other )
    {
        IComponent* hitByComp = dynamic_cast<IComponent*>(other);
        if ( hitByComp )
        {
            GameObject* hitByObject = hitByComp->getGameObject();
            this->getGameObject()->onHit( hitByObject, contact );
        }
    }
}

void Box2DPhysicsComponent::setContactable( bool contactable )
{
    if ( contactable )
    {
        this->mBody->SetUserData( static_cast<void*>(dynamic_cast<IContactable*>(this)) );
    }
    else
    {
        this->mBody->SetUserData( nullptr );
    }
}

void Box2DPhysicsComponent::destroyBody()
{
    mBody->GetWorld()->DestroyBody( mBody );
}
