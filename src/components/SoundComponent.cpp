#include <lib/gameobjects/GameObject.hpp>
#include "lib/components/SoundComponent.hpp"

SoundComponent::SoundComponent( GameObject* gameObject ) :
        mSounds()
        , mGameObject( gameObject )
{
    this->setType( "SoundComponent" );
}

GameObject* SoundComponent::getGameObject() const
{
    return mGameObject;
}

void SoundComponent::update( GameObject* object, sf::Time dt )
{

}

void SoundComponent::addSound( std::string name, sf::Sound sound )
{
    mSounds.emplace( name, sound );
}

sf::Sound* SoundComponent::getSound( std::string name )
{
    try
    {
        return &mSounds.at( name );
    }
    catch( std::out_of_range oor )
    {
        return nullptr;
    }
}
