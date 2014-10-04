#include "lib/gameobjects/Player.hpp"
#include "lib/gameobjects/GameObjectFactory.hpp"
#include "lib/gameobjects/Fireball.hpp"
#include "lib/gameobjects/EnemyA.hpp"

GameObjectFactory::GameObjectFactory()
{

}

GameObject* GameObjectFactory::createObject( World* world, std::string name, sf::Vector2f position, sf::Vector2f size )
{
    if ( name == "Fireball" )
        return new Fireball( world, name, position, size );
    else if ( name == "Player" )
        return new Player( world, name, position, size );
    else if ( name == "EnemyA" )
        return new EnemyA( world, name, position, size );
    else
        return new GameObject( world, name, position, size );
}
