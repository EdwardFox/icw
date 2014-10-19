#ifndef SLASH_HPP
#define SLASH_HPP

#include "lib/gameobjects/GameObject.hpp"

class Slash : public GameObject
{
public:
    Slash( World* world, std::string name, sf::Vector2f position, sf::Vector2f size = sf::Vector2f( 4.f, 4.f) );

    virtual void onHit( GameObject* hitBy, Contact contact ) override;

    void setMovementSpeed( sf::Vector2f movespeed );



private:

    void createDefaultComponents();
};

#endif