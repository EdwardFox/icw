#ifndef DEFAULT_GRAPHIC_COMPONENT_HPP
#define DEFAULT_GRAPHIC_COMPONENT_HPP

#include "IGraphicComponent.hpp"

class DefaultGraphicComponent : public IGraphicComponent
{
    public:
        DefaultGraphicComponent();
        DefaultGraphicComponent(sf::Vector2f position, sf::Vector2f size);

        virtual void update(GameObject& object, sf::Time dt);
        virtual void render(sf::RenderTarget& target, sf::Time dt) const;

    private:
        sf::RectangleShape mShape;
};

#endif
