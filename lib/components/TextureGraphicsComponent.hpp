#ifndef TEXTURE_GRAPHICS_COMPONENT_HPP
#define TEXTURE_GRAPHICS_COMPONENT_HPP

#include "lib/interfaces/IGraphicsComponent.hpp"

class TextureGraphicsComponent : public IGraphicsComponent
{
public:
    TextureGraphicsComponent();

    TextureGraphicsComponent( sf::Texture& texture );

    virtual void update( GameObject& object, sf::Time dt );

    virtual void render( sf::RenderTarget& target, sf::Time dt ) const;

private:
    sf::Sprite mSprite;
};

#endif
