#include "lib/components/DefaultPhysicsComponent.hpp"
#include "lib/GameObject.hpp"

DefaultPhysicsComponent::DefaultPhysicsComponent(b2World& physics, GameObject& object, b2BodyType type)
{
    this->setType("PhysicsComponent");
    createCollisionBody(physics, object, type);
}

void DefaultPhysicsComponent::update(GameObject& object, sf::Time dt)
{
    if(mBody->GetType() != b2_staticBody) {
        object.setPosition(sf::Vector2f(mBody->GetPosition().x * SCALE, mBody->GetPosition().y * SCALE));
        object.setRotation(mBody->GetAngle() * 180.f / 3.14f);
    }
}

void DefaultPhysicsComponent::createCollisionBody(b2World& physics, GameObject& object, b2BodyType type)
{
    // Create instances
    mBodyDef = b2BodyDef();
    mBodyShape = b2PolygonShape();
    mFixtureDef = b2FixtureDef();

    // Set type
    mBodyDef.type = type;
    
    // Set position and create the body
    mBodyDef.position.Set(object.getPosition().x / SCALE, object.getPosition().y / SCALE);
    mBody = physics.CreateBody(&mBodyDef);

    // Box Shape
    mBodyShape.SetAsBox((object.getSize().x / 2.f) / SCALE, (object.getSize().y / 2.f) / SCALE);
    
    // Static
    if(type == b2_staticBody) {
        mBody->CreateFixture(&mBodyShape, 0.f);

    // Dynamic or Kinematic
    } else {
        mFixtureDef.shape = &mBodyShape;
        mFixtureDef.density = 1.f;
        mFixtureDef.friction = 0.3f;
        mBody->CreateFixture(&mFixtureDef);
    }
}
