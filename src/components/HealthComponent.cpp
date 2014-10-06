#include <lib/gameobjects/GameObject.hpp>
#include "lib/components/HealthComponent.hpp"

HealthComponent::HealthComponent( GameObject* gameObject ) :
        mResponses()
        , mGameObject( gameObject )
        , mMaxHealth( 100.f )
        , mHealth( mMaxHealth )
{
    this->setType( "HealthComponent" );
}

void HealthComponent::update( GameObject* object, sf::Time dt )
{
    if( mHealth <= 0.f )
    {
        mGameObject->setExpired( true );
    }
}

GameObject* HealthComponent::getGameObject() const
{
    return mGameObject;
}

float HealthComponent::getHealth() const
{
    return mHealth;
}

float HealthComponent::getMaximumHealth() const
{
    return mMaxHealth;
}

void HealthComponent::receiveDamage( std::string element, float damage )
{
    try
    {
        mResponses.at( element )( mGameObject, damage );
    }
    catch ( std::out_of_range oor )
    {
        /** No special response found => flat reduction */
        mHealth -= damage;
    }
}

void HealthComponent::addDamageResponse( std::string element, std::function<void( GameObject* object, float damage )> function )
{
    mResponses.emplace( element, function );
}

void HealthComponent::setHealth( float health )
{
    mHealth = health;
}

void HealthComponent::setMaximumHealth( float health, bool setHealth )
{
    mMaxHealth = health;

    if(setHealth == true) {
        mHealth = health;
    }
}
