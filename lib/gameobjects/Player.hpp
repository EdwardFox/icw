#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <lib/gameobjects/GameObject.hpp>

class Player : public GameObject
{
public:

    Player( World* world, std::string name, sf::Vector2f position, sf::Vector2f size = sf::Vector2f( 10.f, 11.f ) );

    virtual ~Player()
    {
    };

    virtual void onHit( GameObject* hitBy, Contact contact ) override;

private:

    void createDefaultComponents();
};

#endif