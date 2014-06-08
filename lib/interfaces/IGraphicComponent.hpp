#ifndef GRAPHIC_COMPONENT_HPP
#define GRAPHIC_COMPONENT_HPP

#include "lib/interfaces/IComponent.hpp"

class IGraphicComponent : public IComponent
{
    public:
        virtual void update(GameObject& object, sf::Time dt) = 0;
        virtual void render(sf::RenderTarget& target, sf::Time dt) const = 0;
};

#endif
