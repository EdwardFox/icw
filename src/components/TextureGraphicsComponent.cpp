#include "lib/components/TextureGraphicsComponent.hpp"
#include "lib/GameObject.hpp"

TextureGraphicsComponent::TextureGraphicsComponent() :
        mSprite()
{
    this->setType( "GraphicsComponent" );
}

TextureGraphicsComponent::TextureGraphicsComponent( sf::Texture& texture ) : TextureGraphicsComponent()
{
    mSprite.setTexture( texture );
    mSprite.setOrigin( texture.getSize().x / 2.f, texture.getSize().y / 2.f );
}

void TextureGraphicsComponent::update( GameObject& object, sf::Time dt )
{
    mSprite.setPosition( object.getPosition() );
    mSprite.setRotation( object.getRotation() );
}

void TextureGraphicsComponent::render( sf::RenderTarget& target, sf::Time dt ) const
{
    target.draw( mSprite );
}
