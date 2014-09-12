#include "lib/interfaces/IPhysicsComponent.hpp"
#include "lib/components/PlayerStateHandlerComponent.hpp"
#include "lib/GameObject.hpp"

PlayerStateHandlerComponent::PlayerStateHandlerComponent()
{
    this->setType( "StateHandlerComponent" );
}

void PlayerStateHandlerComponent::update( GameObject& object, sf::Time dt )
{

}
