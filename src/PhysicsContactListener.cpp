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
        IContactable* con = ( IContactable* )fixtureUserData;
        con->onContact( Contact::Begin );
    }

    fixtureUserData = contact->GetFixtureB()->GetUserData();
    if ( fixtureUserData )
    {
        IContactable* con = ( IContactable* )fixtureUserData;
        con->onContact( Contact::Begin );
    }
}

void PhysicsContactListener::EndContact( b2Contact* contact )
{
    void* fixtureUserData = contact->GetFixtureA()->GetUserData();
    if ( fixtureUserData )
    {
        IContactable* con = ( IContactable* )fixtureUserData;
        con->onContact( Contact::End );
    }

    fixtureUserData = contact->GetFixtureB()->GetUserData();
    if ( fixtureUserData )
    {
        IContactable* con = ( IContactable* )fixtureUserData;
        con->onContact( Contact::End );
    }
}
