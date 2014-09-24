#include "lib/GameObject.hpp"
#include <stdexcept>

GameObject::GameObject( World* world ) :
        mWorld( world )
        , mComponents()
        , mGraphicComponent( nullptr )
        , mPosition( 0, 0 )
        , mSize( TILE_SIZE, TILE_SIZE )
        , mVelocity( 0, 0 )
        , mRotation( 0 )
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
        it->second->update( *(this), dt );
    }

    mGraphicComponent->update( *(this), dt );
}

void GameObject::render( sf::RenderTarget& target, sf::Time dt ) const
{
    if ( mGraphicComponent.get() != nullptr )
    {
        mGraphicComponent->render( target, dt );
    }
}

sf::Vector2f GameObject::getPosition() const
{
    return mPosition;
}

sf::Vector2f GameObject::getSize() const
{
    return mSize;
}

sf::Vector2f GameObject::getVelocity() const
{
    return mVelocity;
}

float GameObject::getRotation() const
{
    return mRotation;
}

void GameObject::setPosition( sf::Vector2f position )
{
    mPosition = position;
}

void GameObject::setSize( sf::Vector2f size )
{
    mSize = size;
}

void GameObject::setVelocity( sf::Vector2f velocity )
{
    mVelocity = velocity;
}

void GameObject::setRotation( float rotation )
{
    mRotation = rotation;
}
