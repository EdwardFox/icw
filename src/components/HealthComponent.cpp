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
        mResponses.at( element )( damage );
    }
    catch ( std::out_of_range oor )
    {
        /** No special response found => flat reduction */
        mHealth -= damage;
        if( mHealth < 0.f )
        {
            mHealth = 0.f;
        }
    }
}

void HealthComponent::addDamageResponse( std::string element, std::function<void( std::string, float )> function )
{
    mResponses.emplace( element, function );
}

void HealthComponent::setHealth( float health )
{
    mHealth = health;
}

void HealthComponent::setMaximumHealth( float health )
{
    mMaxHealth = health;
}
