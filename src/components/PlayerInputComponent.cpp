#include <lib/components/AnimationGraphicsComponent.hpp>
#include "lib/components/PlayerMovementComponent.hpp"
#include <lib/interfaces/IStateHandlerComponent.hpp>
#include "lib/components/PlayerInputComponent.hpp"
#include "lib/GameObject.hpp"

PlayerInputComponent::PlayerInputComponent()
{
    this->setType( "InputComponent" );
}

void PlayerInputComponent::update( GameObject& object, sf::Time dt )
{
    IComponent* comp = object.getGraphicComponent();
    AnimationGraphicsComponent* animComp = dynamic_cast<AnimationGraphicsComponent*>(comp);

    IComponent* comp2 = object.getComponent( "MovementComponent" );
    IMovementComponent* moveComp = dynamic_cast<IMovementComponent*>(comp2);

    IStateHandlerComponent* stateComp = dynamic_cast<IStateHandlerComponent*>(object.getComponent( "StateHandlerComponent" ) );

    sf::Vector2f flipped( 1.f, 1.f );
    if ( animComp )
        flipped = animComp->getFlipped();

    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::A ) )
    {
        if ( moveComp )
            moveComp->move( object, Movement::Left );

        flipped.x = -1.f;

        stateComp->changeState( object, "run" );
    }
    else if ( sf::Keyboard::isKeyPressed( sf::Keyboard::D ) )
    {
        if ( moveComp )
            moveComp->move( object, Movement::Right );

        flipped.x = 1.f;

        stateComp->changeState( object, "run" );
    }
    else
    {
        if ( moveComp )
            moveComp->move( object, Movement::Idle );

        stateComp->changeState( object, "idle" );
    }

    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::W ) || sf::Keyboard::isKeyPressed( sf::Keyboard::Space ) )
    {
        if ( moveComp )
        {
            moveComp->jump( object );
        }

        stateComp->changeState( object, "jump" );
    }

    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::E ) )
    {
        stateComp->changeState( object, "attack" );
    }

    if ( animComp )
        animComp->setFlipped( flipped );
}
