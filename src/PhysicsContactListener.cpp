#include "lib/PhysicsContactListener.hpp"
#include "lib/interfaces/IContactable.hpp"

PhysicsContactListener::PhysicsContactListener()
{
}

void PhysicsContactListener::BeginContact( b2Contact* contact )
{
    /** On contact with fixtureA **/
    void* fixtureUserData = contact->GetFixtureA()->GetUserData();
    if ( fixtureUserData )
    {
        IContactable* con = static_cast<IContactable*>(fixtureUserData);
        con->onContact( Contact::Begin, nullptr, contact->GetFixtureB()->GetBody()->GetType() );
    }

    /** On contact with fixtureB **/
    fixtureUserData = contact->GetFixtureB()->GetUserData();
    if ( fixtureUserData )
    {
        IContactable* con = static_cast<IContactable*>(fixtureUserData);
        con->onContact( Contact::Begin, nullptr, contact->GetFixtureA()->GetBody()->GetType() );
    }

    /** On contact with bodyA **/
    void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
    if( bodyUserDataA )
    {
        IContactable* conA = static_cast<IContactable*>(bodyUserDataA);
        conA->onContact( Contact::Begin, nullptr, contact->GetFixtureB()->GetBody()->GetType() );
    }

    /** On contact with bodyB **/
    void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();
    if( bodyUserDataB )
    {
        IContactable* conB = static_cast<IContactable*>(bodyUserDataB);
        conB->onContact( Contact::Begin, nullptr, contact->GetFixtureA()->GetBody()->GetType() );
    }

    /** On contact with bodyA & bodyB **/
    if ( bodyUserDataA && bodyUserDataB )
    {
        IContactable* conA = static_cast<IContactable*>(bodyUserDataA);
        IContactable* conB = static_cast<IContactable*>(bodyUserDataB);

        conA->onContact( Contact::Begin, conB, contact->GetFixtureB()->GetBody()->GetType() );
        conB->onContact( Contact::Begin, conA, contact->GetFixtureA()->GetBody()->GetType() );
    }
}

void PhysicsContactListener::EndContact( b2Contact* contact )
{
    /** On contact with fixtureA **/
    void* fixtureUserData = contact->GetFixtureA()->GetUserData();
    if ( fixtureUserData )
    {
        IContactable* con = static_cast<IContactable*>(fixtureUserData);
        con->onContact( Contact::End, nullptr, contact->GetFixtureB()->GetBody()->GetType() );
    }

    /** On contact with fixtureB **/
    fixtureUserData = contact->GetFixtureB()->GetUserData();
    if ( fixtureUserData )
    {
        IContactable* con = static_cast<IContactable*>(fixtureUserData);
        con->onContact( Contact::End, nullptr, contact->GetFixtureA()->GetBody()->GetType() );
    }

    /** On contact with bodyA & bodyB **/
    void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
    void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();
    if ( bodyUserDataA && bodyUserDataB )
    {
        IContactable* conA = static_cast<IContactable*>(bodyUserDataA);
        IContactable* conB = static_cast<IContactable*>(bodyUserDataB);
        conA->onContact( Contact::End, conB, contact->GetFixtureB()->GetBody()->GetType() );
        conB->onContact( Contact::End, conA, contact->GetFixtureA()->GetBody()->GetType() );
    }
}

void PhysicsContactListener::PreSolve( b2Contact* contact, const b2Manifold* oldManifold )
{
    void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
    void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();

    /** On contact with bodyA & bodyB **/
    if ( bodyUserDataA && bodyUserDataB )
    {
        IContactable* conA = static_cast<IContactable*>(bodyUserDataA);
        IContactable* conB = static_cast<IContactable*>(bodyUserDataB);

        conA->onContact( Contact::PreSolve, conB, contact->GetFixtureB()->GetBody()->GetType() );
        conB->onContact( Contact::PreSolve, conA, contact->GetFixtureA()->GetBody()->GetType() );

        /** Disable collision if two dynamic objects touch each other **/
        contact->SetEnabled( false );
    }
}

void PhysicsContactListener::PostSolve( b2Contact* contact, const b2ContactImpulse* impulse )
{
}
