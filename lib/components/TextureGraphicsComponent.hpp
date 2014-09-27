#ifndef TEXTURE_GRAPHICS_COMPONENT_HPP
#define TEXTURE_GRAPHICS_COMPONENT_HPP

#include <lib/GameObject.hpp>
#include "lib/interfaces/IGraphicsComponent.hpp"

class TextureGraphicsComponent : public IGraphicsComponent
{
public:
    TextureGraphicsComponent( GameObject* gameObject );

    TextureGraphicsComponent( GameObject* gameObject, sf::Texture& texture );

    virtual ~TextureGraphicsComponent() {};

    virtual void update( GameObject* object, sf::Time dt ) override;

    virtual void render( sf::RenderTarget& target, sf::Time dt ) const override;

    virtual void setTexture( sf::Texture* texture, sf::IntRect rect );

    virtual GameObject* getGameObject() const override;

private:
    sf::Texture* mTexture;
    GameObject* mGameObject;
    sf::Sprite mSprite;
};

#endif
