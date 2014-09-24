#include "lib/PhysicsContactListener.hpp"
#include "lib/interfaces/IContactable.hpp"

PhysicsContactListener::PhysicsContactListener()
{
}

void PhysicsContactListener::BeginContact( b2Contact* contact )
{
    void* fixtureUserData = contact->GetFixtureA()->GetUserData();
    if ( fixtureUserData )
    {
        IContactable* con = static_cast<IContactable*>(fixtureUserData);
        con->onContact( Contact::Begin );
    }

    fixtureUserData = contact->GetFixtureB()->GetUserData();
    if ( fixtureUserData )
    {
        IContactable* con = static_cast<IContactable*>(fixtureUserData);
        con->onContact( Contact::Begin );
    }

    void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
    void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();
    if ( bodyUserDataA && bodyUserDataB )
    {
        IContactable* conA = static_cast<IContactable*>(bodyUserDataA);
        IContactable* conB = static_cast<IContactable*>(bodyUserDataB);
        conA->onContact( Contact::Begin, conB );
        conB->onContact( Contact::Begin, conA );
    }
}

void PhysicsContactListener::EndContact( b2Contact* contact )
{
    void* fixtureUserData = contact->GetFixtureA()->GetUserData();
    if ( fixtureUserData )
    {
        IContactable* con = static_cast<IContactable*>(fixtureUserData);
        con->onContact( Contact::End );
    }

    fixtureUserData = contact->GetFixtureB()->GetUserData();
    if ( fixtureUserData )
    {
        IContactable* con = static_cast<IContactable*>(fixtureUserData);
        con->onContact( Contact::End );
    }

    void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
    void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();
    if ( bodyUserDataA && bodyUserDataB )
    {
        IContactable* conA = static_cast<IContactable*>(bodyUserDataA);
        IContactable* conB = static_cast<IContactable*>(bodyUserDataB);
        conA->onContact( Contact::End, conB );
        conB->onContact( Contact::End, conA );
    }
}
