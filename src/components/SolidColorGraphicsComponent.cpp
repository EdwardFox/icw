#include "lib/components/SolidColorGraphicsComponent.hpp"
#include "lib/gameobjects/GameObject.hpp"

SolidColorGraphicsComponent::SolidColorGraphicsComponent( GameObject* gameObject ) :
        mShape()
        , mGameObject( gameObject )
{
    this->setType( "GraphicsComponent" );

    mShape.setFillColor( sf::Color::White );
    mShape.setOutlineColor( sf::Color::Black );
    mShape.setOutlineThickness( 1.f );
}

SolidColorGraphicsComponent::SolidColorGraphicsComponent( GameObject* gameObject, sf::Vector2f size ) : SolidColorGraphicsComponent( gameObject )
{
    mShape.setSize( size );
    mShape.setOrigin( size.x / 2.f, size.y / 2.f );
}

void SolidColorGraphicsComponent::update( GameObject* object, sf::Time dt )
{
    mShape.setPosition( object->getPosition() );
    mShape.setSize( object->getSize() );
    mShape.setRotation( object->getRotation() );
}

void SolidColorGraphicsComponent::render( sf::RenderTarget& target, sf::Time dt ) const
{
    target.draw( mShape );
}

GameObject* SolidColorGraphicsComponent::getGameObject() const
{
    return mGameObject;
}
