#include "lib/interfaces/IPhysicsComponent.hpp"
#include "lib/components/TestInputComponent.hpp"
#include "lib/GameObject.hpp"

TestInputComponent::TestInputComponent()
{
    this->setType( "InputComponent" );
}

void TestInputComponent::update( GameObject& object, sf::Time dt )
{
    b2Vec2 velocity = b2Vec2( 0.f, 0.f );

    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::A ) )
    {
        velocity.x = -3.f;
    }

    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::D ) )
    {
        velocity.x = 3.f;
    }

    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::W ) )
    {
        velocity.y = -5.f;
    }

    ComponentCommand<IPhysicsComponent&> command;
    command.targetType = "PhysicsComponent";
    command.execute = [velocity]( IPhysicsComponent& comp )
    {
        if ( comp.getBodyType() != b2_staticBody )
        {
            b2Vec2 vel = comp.getLinearVelocity();
            if( velocity.x != 0 )
                vel.x = velocity.x;

            if( velocity.y != 0 )
                vel.y = velocity.y;

            comp.setLinearVelocity( vel );
        }
    };
    object.broadcastComponentCommand( command );
}
