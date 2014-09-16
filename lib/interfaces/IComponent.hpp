#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <SFML/Graphics.hpp>

// Forward declaration
class GameObject;

class IComponent
{
public:
    virtual void update( GameObject& object, sf::Time dt ) = 0;

    std::string getType() const
    {
        return mType;
    }

    void setType( std::string type )
    {
        mType = type;
    }

private:
    std::string mType;
};

#endif
