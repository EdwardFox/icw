#include <lib/gameobjects/GameObject.hpp>
#include "lib/components/SpawnerComponent.hpp"
#include "lib/World.hpp"

SpawnerComponent::SpawnerComponent( GameObject* gameObject ) :
        mGameObject( gameObject )
        , mTimer()
        , mRandomTime( 0.f )
{
    this->setType( "SpawnerComponent" );
}

void SpawnerComponent::update( GameObject* object, sf::Time dt )
{
    if ( mTimer.getElapsedTime().asMilliseconds() >= mRandomTime )
    {
        this->spawn();

        /** Restart **/
        mTimer.restart();
        std::random_device rd;
        std::mt19937 eng( rd() );
        std::uniform_int_distribution<> distr( this->getIntervalMin(), this->getIntervalMax() );
        mRandomTime = static_cast<unsigned>(distr( eng ));
    }
}

GameObject* SpawnerComponent::getGameObject() const
{
    return mGameObject;
}

void SpawnerComponent::spawn()
{
    sf::Vector2f position = mGameObject->getPosition();
    sf::Vector2f size = mGameObject->getSize();

    World* world = mGameObject->getWorld();
    GameObject* object = world->createGameObject( this->getGameObjectType(), position, size );
    object->setProperties( *this->getProperties() );
}
