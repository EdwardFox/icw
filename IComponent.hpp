#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <SFML/Graphics.hpp>
#include "GameObject.hpp"

// Forward declaration
class GameObject;

class IComponent
{
    public:
        virtual void update(GameObject& object, sf::Time dt) = 0;
        virtual std::string getType() { return mType; }
        virtual void setType(std::string type) { mType = type; }

    private:
        std::string mType;
};

#endif
