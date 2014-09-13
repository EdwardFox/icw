#include "lib/interfaces/IPhysicsComponent.hpp"
#include "lib/components/DefaultStateHandlerComponent.hpp"
#include "lib/GameObject.hpp"

DefaultStateHandlerComponent::DefaultStateHandlerComponent()
{
    this->setType( "StateHandlerComponent" );
}

void DefaultStateHandlerComponent::update( GameObject& object, sf::Time dt )
{

}
