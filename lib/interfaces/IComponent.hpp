#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <SFML/Graphics.hpp>
#include "lib/components/ComponentCommand.hpp"

// Forward declaration
class GameObject;

class IComponent
{
    public:
        virtual void update(GameObject& object, sf::Time dt) = 0;
        std::string getType() { return mType; }
        void setType(std::string type) { mType = type; }

        template<typename T>
        void onCommand(ComponentCommand<T&> command) {
            if(command.targetType == mType) {
                if(T* temp = dynamic_cast<T*>(this)) {
                    command.execute(*temp);
                } else {
                    // Unsuccessful cast
                }
            }
        }

    private:
        std::string mType;
};

#endif
