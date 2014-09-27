#include "lib/GameObject.hpp"
#include <stdexcept>
#include <lib/interfaces/IContactable.hpp>

GameObject::GameObject( World* world, std::string name ) :
        mWorld( world )
        , mComponents()
        , mGraphicComponent( nullptr )
        , mPosition( 0, 0 )
        , mSize( TILE_SIZE, TILE_SIZE )
        , mVelocity( 0, 0 )
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
    std::cout << "Object '" << this->getName() << "' was hit by '" << hitBy->getName() << "'" << std::endl;
    // map.at(this->getName())( ... );
}
