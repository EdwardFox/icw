#include "DefaultGraphicComponent.hpp"

DefaultGraphicComponent::DefaultGraphicComponent() :
mShape()
{
    this->setType("defaultGraphics");

    mShape.setFillColor(sf::Color::White);
    mShape.setOutlineColor(sf::Color::Black);
    mShape.setOutlineThickness(1.f);
}

DefaultGraphicComponent::DefaultGraphicComponent(sf::Vector2f position, sf::Vector2f size) : DefaultGraphicComponent()
{
    mShape.setPosition(position);
    mShape.setSize(size);
}

void DefaultGraphicComponent::update(GameObject& object, sf::Time dt)
{
    //mShape.setPosition(object.getPosition());
    //mShape.setSize(object.getSize());
}

void DefaultGraphicComponent::render(sf::RenderTarget& target, sf::Time dt) const
{
    target.draw(mShape);
}
