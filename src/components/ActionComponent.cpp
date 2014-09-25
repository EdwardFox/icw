#include <lib/GameObject.hpp>
#include "lib/components/ActionComponent.hpp"

ActionComponent::ActionComponent( GameObject* gameObject ) :
        mActions()
        , mGameObject( gameObject )
{
    this->setType( "ActionComponent" );
}

void ActionComponent::update( GameObject& object, sf::Time dt )
{

}

void ActionComponent::addAction( std::string key, std::function<void( GameObject& object )> action )
{
    mActions.emplace( key, action );
}

void ActionComponent::executeAction( std::string key, GameObject& object )
{
    mActions.at( key )( object );
}

GameObject* ActionComponent::getGameObject() const
{
    return mGameObject;
}
