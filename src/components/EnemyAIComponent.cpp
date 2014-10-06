#include <lib/interfaces/ICharacterMovementComponent.hpp>
#include <lib/interfaces/IStateHandlerComponent.hpp>
#include <lib/components/AnimationGraphicsComponent.hpp>
#include "lib/interfaces/IPhysicsComponent.hpp"
#include "lib/components/EnemyAIComponent.hpp"

EnemyAIComponent::EnemyAIComponent( GameObject* gameObject ) :
        mGameObject( gameObject )
        , mTimeAlive( 0 )
        , mMaxTimeAlive( 0 ) // Enemy may only live 3000 milliseconds
        , mRunLeft( 1 ) // Enemy may only live 3000 milliseconds
{
    this->setType( "EnemyAIComponent" );

    mMaxTimeAlive = (rand()%(4000-1000))+1000;
}

void EnemyAIComponent::update( GameObject* object, sf::Time dt )
{
    IStateHandlerComponent* stateComp = dynamic_cast<IStateHandlerComponent*>(object->getComponent( "StateHandlerComponent" ) );
    AnimationGraphicsComponent* animComp = dynamic_cast<AnimationGraphicsComponent*>(object->getGraphicComponent());

    sf::Vector2f flipped( 1.f, 1.f );

    if ( animComp )
        flipped = animComp->getFlipped();

    ICharacterMovementComponent* moveComp = dynamic_cast<ICharacterMovementComponent*>( object->getComponent( "MovementComponent" ) );
    if ( moveComp )
    {
        if(mRunLeft == 1) {
            moveComp->move( object, Movement::Left );
            stateComp->changeState( object, "run" );
            flipped.x = -1.f;
        } else
        {
            moveComp->move( object, Movement::Right );
            stateComp->changeState( object, "run" );
            flipped.x = 1.f;
        }
    }

    if ( animComp )
        animComp->setFlipped( flipped );


    /** Kill Enemy if it has lived longer than its maximum lifespan **/
    if( mTimeAlive >= mMaxTimeAlive )
    {
        mRunLeft = -mRunLeft;
        mTimeAlive = 0;
    }
    else
    {
        mTimeAlive += dt.asMilliseconds();
    }
}



