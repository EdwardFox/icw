#include "lib/interfaces/IStateHandlerComponent.hpp"
#include "lib/components/PlayerInputComponent.hpp"
#include "lib/GameObject.hpp"

PlayerInputComponent::PlayerInputComponent()
{
    this->setType( "InputComponent" );
}

void PlayerInputComponent::update( GameObject& object, sf::Time dt )
{
    changeState( object, "fall" );
    changeState( object, "idle" );


    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::A ) )
    {
        changeState( object, "runLeft" );
        changeState( object, "fallLeft" );
    }

    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::D ) )
    {
        changeState( object, "runRight" );
        changeState( object, "fallRight" );
    }

    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::W ) )
    {
        changeState( object, "jump" );
    }
}

void PlayerInputComponent::changeState( GameObject& object, std::string state ) const
{
    // Tell the state component to change its state
    ComponentCommand<IStateHandlerComponent&> stateCommand;
    stateCommand.targetType = "StateHandlerComponent";
    stateCommand.execute = [&object, state]( IStateHandlerComponent& comp )
    {
        comp.onAction( state, object );
    };
    object.broadcastComponentCommand( stateCommand );

}
