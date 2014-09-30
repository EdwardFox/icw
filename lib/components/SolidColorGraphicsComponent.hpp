#ifndef SOLID_COLOR_GRAPHICS_COMPONENT_HPP
#define SOLID_COLOR_GRAPHICS_COMPONENT_HPP

#include <lib/gameobjects/GameObject.hpp>
#include "lib/interfaces/IGraphicsComponent.hpp"

class SolidColorGraphicsComponent : public IGraphicsComponent
{
public:
    SolidColorGraphicsComponent( GameObject* gameObject );

    SolidColorGraphicsComponent( GameObject* gameObject, sf::Vector2f size );

    virtual ~SolidColorGraphicsComponent() {};

    virtual void update( GameObject* object, sf::Time dt ) override;

    virtual void render( sf::RenderTarget& target, sf::Time dt ) const override;

    virtual GameObject* getGameObject() const override;

private:
    sf::RectangleShape mShape;
    GameObject* mGameObject;
};

#endif
