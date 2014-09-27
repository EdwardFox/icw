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
        con->onContact( Contact::Begin, nullptr );
    }

    /** On contact with fixtureB **/
    fixtureUserData = contact->GetFixtureB()->GetUserData();
    if ( fixtureUserData )
    {
        IContactable* con = static_cast<IContactable*>(fixtureUserData);
        con->onContact( Contact::Begin, nullptr );
    }

    /** On contact with bodyA **/
    void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
    if( bodyUserDataA )
    {
        IContactable* conA = static_cast<IContactable*>(bodyUserDataA);
        conA->onContact( Contact::Begin, nullptr );
    }

    /** On contact with bodyB **/
    void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();
    if( bodyUserDataB )
    {
        IContactable* conB = static_cast<IContactable*>(bodyUserDataB);
        conB->onContact( Contact::Begin, nullptr );
    }

    /** On contact with bodyA & bodyB **/
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
    /** On contact with fixtureA **/
    void* fixtureUserData = contact->GetFixtureA()->GetUserData();
    if ( fixtureUserData )
    {
        IContactable* con = static_cast<IContactable*>(fixtureUserData);
        con->onContact( Contact::End, nullptr );
    }

    /** On contact with fixtureB **/
    fixtureUserData = contact->GetFixtureB()->GetUserData();
    if ( fixtureUserData )
    {
        IContactable* con = static_cast<IContactable*>(fixtureUserData);
        con->onContact( Contact::End, nullptr );
    }

    /** On contact with bodyA & bodyB **/
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
