#ifndef SOLID_COLOR_GRAPHICS_COMPONENT_HPP
#define SOLID_COLOR_GRAPHICS_COMPONENT_HPP

#include "lib/interfaces/IGraphicsComponent.hpp"

class SolidColorGraphicsComponent : public IGraphicsComponent
{
public:
    SolidColorGraphicsComponent();

    SolidColorGraphicsComponent( sf::Vector2f size );

    virtual void update( GameObject& object, sf::Time dt );

    virtual void render( sf::RenderTarget& target, sf::Time dt ) const;

private:
    sf::RectangleShape mShape;
};

#endif
