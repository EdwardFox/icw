#ifndef IPHYSICS_COMPONENT_HPP
#define IPHYSICS_COMPONENT_HPP

#include <Box2D/Box2D.h>

class GameObject;

class IPhysicsComponent
{
    public:
        virtual void createCollisionBody(b2World& physics, GameObject& object, b2BodyType type) = 0;

        b2BodyType getBodyType() { return mBody->GetType(); }

        b2Vec2 getLinearVelocity() { return mBody->GetLinearVelocity(); }
        void setLinearVelocity(b2Vec2 vel) { mBody->SetLinearVelocity(vel); }

    protected:
        b2BodyDef mBodyDef;
        b2Body* mBody;
        b2PolygonShape mBodyShape;
        b2FixtureDef mFixtureDef;
};

#endif
