#ifndef ENEMYA_HPP
#define ENEMYA_HPP

#include "lib/gameobjects/GameObject.hpp"

class EnemyA : public GameObject
{
public:
    EnemyA( World* world, std::string name, sf::Vector2f position, sf::Vector2f size = sf::Vector2f( 4.f, 4.f) );

    virtual void onHit( GameObject* hitBy, Contact contact ) override;


    virtual void setProperties( std::vector<std::tuple<std::string, std::string>> properties ) override;

private:

    void createDefaultComponents();
};

#endif