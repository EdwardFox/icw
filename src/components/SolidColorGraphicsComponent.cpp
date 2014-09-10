#include "lib/components/SolidColorGraphicsComponent.hpp"
#include "lib/GameObject.hpp"

SolidColorGraphicsComponent::SolidColorGraphicsComponent() :
        mShape()
{
    this->setType( "GraphicsComponent" );

    mShape.setFillColor( sf::Color::White );
    mShape.setOutlineColor( sf::Color::Black );
    mShape.setOutlineThickness( 1.f );
}

SolidColorGraphicsComponent::SolidColorGraphicsComponent( sf::Vector2f size ) : SolidColorGraphicsComponent()
{
    mShape.setSize( size );
    mShape.setOrigin( size.x / 2.f, size.y / 2.f );
}

void SolidColorGraphicsComponent::update( GameObject& object, sf::Time dt )
{
    mShape.setPosition( object.getPosition() );
    mShape.setSize( object.getSize() );
    mShape.setRotation( object.getRotation() );
}

void SolidColorGraphicsComponent::render( sf::RenderTarget& target, sf::Time dt ) const
{
    target.draw( mShape );
}
