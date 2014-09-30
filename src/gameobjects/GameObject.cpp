#include "lib/gameobjects/GameObject.hpp"
#include <stdexcept>
#include <lib/interfaces/IContactable.hpp>

GameObject::GameObject( World* world, std::string name, sf::Vector2f position, sf::Vector2f size ) :
        mWorld( world )
        , mComponents()
        , mGraphicComponent( nullptr )
        , mPosition( position )
        , mSize( size )
        , mExpired( false )
        , mRotation( 0 )
        , mName( name )
{

}

void GameObject::attachComponent( std::string key, IComponent* component )
{
    mComponents.emplace( key, std::unique_ptr<IComponent>( component ) );
}

void GameObject::detachComponent( std::string key )
{
    mComponents.erase( key );
}

IComponent* const GameObject::getComponent( std::string key ) const
{
    try
    {
        return mComponents.at( key ).get();
    }
    catch ( const std::out_of_range& oor )
    {
        return nullptr;
    }
}

void GameObject::setGraphicComponent( IGraphicsComponent* component )
{
    mGraphicComponent = std::unique_ptr<IGraphicsComponent>( component );
}

IGraphicsComponent* const GameObject::getGraphicComponent() const
{
    return mGraphicComponent.get();
}

void GameObject::update( sf::Time dt )
{
    for ( auto it = mComponents.begin(); it != mComponents.end(); ++it )
    {
        it->second->update( this, dt );
    }

    mGraphicComponent->update( this, dt );
}

void GameObject::render( sf::RenderTarget& target, sf::Time dt ) const
{
    if ( mGraphicComponent.get() != nullptr )
    {
        mGraphicComponent->render( target, dt );
    }
}

void GameObject::onHit( GameObject* hitBy, Contact contact )
{
    if ( hitBy )
    {
        std::cout << "Object '" << this->getName() << "' collided with object '" << hitBy->getName() << "'" << std::endl;
    }
    else
    {
//        std::cout << "Object '" << this->getName() << "' collided with object a wall" << std::endl;
    }
}
