#ifndef TEXTURE_GRAPHICS_COMPONENT_HPP
#define TEXTURE_GRAPHICS_COMPONENT_HPP

#include "lib/interfaces/IGraphicsComponent.hpp"

class TextureGraphicsComponent : public IGraphicsComponent
{
public:
    TextureGraphicsComponent();

    TextureGraphicsComponent( sf::Texture& texture );

    virtual ~TextureGraphicsComponent() {};

    virtual void update( GameObject& object, sf::Time dt );

    virtual void render( sf::RenderTarget& target, sf::Time dt ) const;

    virtual void setTexture( sf::Texture& texture, sf::IntRect rect );

private:
    sf::Texture* mTexture;
    sf::Sprite mSprite;
};

#endif
