#include "lib/PhysicsGroundContactListener.hpp"
#include <iostream>
#include <cstdint>

PhysicsGroundContactListener::PhysicsGroundContactListener() :
        mNumGroundContacts( 0 )
        , mTag( 0 )
{

}

void PhysicsGroundContactListener::BeginContact( b2Contact* contact )
{
    //check if fixture A was the foot sensor
    void* fixtureUserData = contact->GetFixtureA()->GetUserData();
    if ( fixtureUserData )
    {
        if ( ( intptr_t )fixtureUserData == mTag )
        {
            ++mNumGroundContacts;
        }
    }
    //check if fixture B was the foot sensor
    fixtureUserData = contact->GetFixtureB()->GetUserData();
    if ( fixtureUserData )
    {
        if ( ( intptr_t )fixtureUserData == mTag )
        {
            ++mNumGroundContacts;
        }
    }
}

void PhysicsGroundContactListener::EndContact( b2Contact* contact )
{
    //check if fixture A was the foot sensor
    void* fixtureUserData = contact->GetFixtureA()->GetUserData();
    if ( fixtureUserData )
    {
        if ( ( intptr_t )fixtureUserData == mTag )
        {
            --mNumGroundContacts;
        }
    }
    //check if fixture B was the foot sensor
    fixtureUserData = contact->GetFixtureB()->GetUserData();
    if ( fixtureUserData )
    {
        if ( ( intptr_t )fixtureUserData == mTag )
        {
            --mNumGroundContacts;
        }
    }
}

int PhysicsGroundContactListener::getNumGroundContacts() const
{
    return mNumGroundContacts;
}
