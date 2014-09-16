#include "lib/PhysicsContactListener.hpp"
#include <iostream>
#include <cstdint>

PhysicsContactListener::PhysicsContactListener() :
        mNumContacts( 0 )
        , mTag( 0 )
{

}

void PhysicsContactListener::BeginContact( b2Contact* contact )
{
    //check if fixture A was the foot sensor
    void* fixtureUserData = contact->GetFixtureA()->GetUserData();
    if ( fixtureUserData )
    {
        if ( ( intptr_t )fixtureUserData == mTag )
        {
            ++mNumContacts;
            std::cout << mTag << std::endl;
        }
    }
    //check if fixture B was the foot sensor
    fixtureUserData = contact->GetFixtureB()->GetUserData();
    if ( fixtureUserData )
    {
        if ( ( intptr_t )fixtureUserData == mTag )
        {
            ++mNumContacts;
            std::cout << mTag << std::endl;
        }
    }
}

void PhysicsContactListener::EndContact( b2Contact* contact )
{
    //check if fixture A was the foot sensor
    void* fixtureUserData = contact->GetFixtureA()->GetUserData();
    if ( fixtureUserData )
    {
        if ( ( intptr_t )fixtureUserData == mTag )
        {
            --mNumContacts;
        }
    }
    //check if fixture B was the foot sensor
    fixtureUserData = contact->GetFixtureB()->GetUserData();
    if ( fixtureUserData )
    {
        if ( ( intptr_t )fixtureUserData == mTag )
        {
            --mNumContacts;
        }
    }
}

int PhysicsContactListener::getNumContacts() const
{
    return mNumContacts;
}

int PhysicsContactListener::getTag() const
{
    return mTag;
}

void PhysicsContactListener::setTag( int tag )
{
    mTag = tag;
}

