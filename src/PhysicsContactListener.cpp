#include "lib/PhysicsContactListener.hpp"

PhysicsContactListener::PhysicsContactListener() :
        mContacts()
{

}

void PhysicsContactListener::BeginContact( b2Contact* contact )
{
    void* fixtureUserData = contact->GetFixtureA()->GetUserData();
    if ( fixtureUserData )
    {
        intptr_t tag = ( intptr_t )fixtureUserData;
        if ( this->tagExists( tag ) )
        {
            mContacts.at( tag )++;
        }
        else
        {
            mContacts.emplace( tag, 0 );
        }
    }

    fixtureUserData = contact->GetFixtureB()->GetUserData();
    if ( fixtureUserData )
    {
        intptr_t tag = ( intptr_t )fixtureUserData;
        if ( this->tagExists( tag ) )
        {
            mContacts.at( tag )++;
        }
        else
        {
            mContacts.emplace( tag, 0 );
        }
    }
}

void PhysicsContactListener::EndContact( b2Contact* contact )
{
    void* fixtureUserData = contact->GetFixtureA()->GetUserData();
    if ( fixtureUserData )
    {
        intptr_t tag = ( intptr_t )fixtureUserData;
        if ( this->tagExists( tag ) )
        {
            mContacts.at( tag )--;
        }
        else
        {
            mContacts.emplace( tag, 0 );
        }
    }

    fixtureUserData = contact->GetFixtureB()->GetUserData();
    if ( fixtureUserData )
    {
        intptr_t tag = ( intptr_t )fixtureUserData;
        if ( this->tagExists( tag ) )
        {
            mContacts.at( tag )--;
        }
        else
        {
            mContacts.emplace( tag, 0 );
        }
    }
}

int PhysicsContactListener::getNumContacts( int tag ) const
{
    try
    {
        return mContacts.at( tag );
    }
    catch ( std::out_of_range oor )
    {
        return 0;
    }
}

bool PhysicsContactListener::tagExists( int tag ) const
{
    try
    {
        mContacts.at( tag );
        return true;
    }
    catch ( std::out_of_range oor )
    {
        return false;
    }

}
