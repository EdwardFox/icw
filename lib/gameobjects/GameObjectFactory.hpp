#ifndef GAMEOBJECT_FACTORY_HPP
#define GAMEOBJECT_FACTORY_HPP

#include <string>

class GameObject;

class World;

class GameObjectFactory
{
public:
    GameObjectFactory();

    GameObject* createObject( World* world, std::string name, sf::Vector2f position, sf::Vector2f size );

private:
};

#endif