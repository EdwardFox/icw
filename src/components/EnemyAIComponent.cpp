#include <lib/interfaces/ICharacterMovementComponent.hpp>
#include <lib/interfaces/IStateHandlerComponent.hpp>
#include <lib/components/AnimationGraphicsComponent.hpp>
#include <lib/components/Box2DPhysicsComponent.hpp>
#include <lib/components/ActionComponent.hpp>
#include <lib/interfaces/ISoundComponent.hpp>
#include "lib/interfaces/IPhysicsComponent.hpp"
#include "lib/components/EnemyAIComponent.hpp"
#include "lib/World.hpp"

EnemyAIComponent::EnemyAIComponent( GameObject* gameObject ) :
        mGameObject( gameObject )
        , mTimeAlive( 0 )
        , mMaxTimeAlive( 0 ) // Enemy may only live 3000 milliseconds
        , mRunLeft( 1 )
        , mSearchAreaSize( 200.f, 200.f )
{
    this->setType( "EnemyAIComponent" );

    mMaxTimeAlive = (rand() % (4000 - 1000)) + 1000;
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
        const GameObject* player = this->getGameObject()->getWorld()->getPlayer();
        sf::FloatRect area;
        area.left = this->getGameObject()->getPosition().x - mSearchAreaSize.x / 2.f;
        area.top = this->getGameObject()->getPosition().y - mSearchAreaSize.y / 2.f;
        area.width = mSearchAreaSize.x;
        area.height = mSearchAreaSize.y;

        if ( player )//&& area.contains( player->getPosition() ) )
        {
            if ( player->getPosition().x < this->getGameObject()->getPosition().x )
            {
                moveComp->move( object, Movement::Left );
                stateComp->changeState( object, "run" );
                flipped.x = -1.f;
            }
            else
            {
                moveComp->move( object, Movement::Right );
                stateComp->changeState( object, "run" );
                flipped.x = 1.f;
            }

            Box2DPhysicsComponent* phys = dynamic_cast<Box2DPhysicsComponent*>( this->getGameObject()->getComponent( "PhysicsComponent" ) );
            if ( phys )
            {
                if ( Collision::None != phys->hitWall() )
                {
                    moveComp->jump( this->getGameObject() );
                }
            }

            float distance = std::sqrt( std::pow( (player->getPosition().x - this->getGameObject()->getPosition().x), 2 ) +
                    std::pow( (player->getPosition().y - this->getGameObject()->getPosition().y), 2 )
            );

            if ( distance < 15.f )
            {
                ActionComponent* action = dynamic_cast<ActionComponent*>( this->getGameObject()->getComponent( "ActionComponent" ) );
                if ( action )
                {
                    bool success = stateComp->changeState( object, "attack" );

                    const Animation* current = animComp->getCurrentAnimation();
                    if ( current->getAnimationName() == "attack" && current->getCurrentFrameNumber() == ( int )(current->getNumFrames() / 2.f - 2) )
                    {
                        action->executeAction( "shoot", this->getGameObject() );

                    }

                    if( success )
                    {
                        ISoundComponent* soundComp = dynamic_cast<ISoundComponent*>(object->getComponent( "SoundComponent" ));
                        if ( soundComp )
                        {
                            soundComp->getSound( "clap" )->play();
                        }
                    }
                }
            }
        }
        else
        {
            if ( mRunLeft == 1 )
            {
                moveComp->move( object, Movement::Left );
                stateComp->changeState( object, "run" );
                flipped.x = -1.f;
            }
            else
            {
                moveComp->move( object, Movement::Right );
                stateComp->changeState( object, "run" );
                flipped.x = 1.f;
            }
        }

    }

    if ( animComp )
        animComp->setFlipped( flipped );


    /** Kill Enemy if it has lived longer than its maximum lifespan **/
    if ( mTimeAlive >= mMaxTimeAlive )
    {
        mRunLeft = -mRunLeft;
        mTimeAlive = 0;
    }
    else
    {
        mTimeAlive += dt.asMilliseconds();
    }
}



