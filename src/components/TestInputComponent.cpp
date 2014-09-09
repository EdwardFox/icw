#include "lib/components/TestInputComponent.hpp"
#include "lib/GameObject.hpp"

TestInputComponent::TestInputComponent()
{
    this->setType("InputComponent");
}

void TestInputComponent::update(GameObject& object, sf::Time dt)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        sf::Vector2f pos = object.getPosition();
        pos.x += -1000.f;
        object.setPosition(pos);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        sf::Vector2f pos = object.getPosition();
        pos.x += 1000.f;
        object.setPosition(pos);
    }
}
