#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <memory>
#include <string>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "lib/Data.hpp"
#include "lib/components/DefaultGraphicComponent.hpp"

// Forward Declaration
class IComponent;
class IGraphicComponent;

class GameObject
{
    public:
        GameObject();

        void attachComponent(std::string key, IComponent* component);
        void detachComponent(std::string key);
        IComponent* const getComponent(std::string key) const;
        void setGraphicComponent(IGraphicComponent* component);
        IGraphicComponent* const getGraphicComponent() const;

        void update(sf::Time dt);
        void render(sf::RenderTarget& target, sf::Time dt) const;

        sf::Vector2f getPosition() const;
        sf::Vector2f getSize() const;
        sf::Vector2f getVelocity() const;
        float getRotation() const;

        void setPosition(sf::Vector2f position);
        void setSize(sf::Vector2f size);
        void setVelocity(sf::Vector2f velocity);
        void setRotation(float rotation);

    private:
        std::unordered_map<std::string, std::unique_ptr<IComponent>> mComponents;
        std::unique_ptr<IGraphicComponent> mGraphicComponent;

        sf::Vector2f mPosition;
        sf::Vector2f mSize;
        sf::Vector2f mVelocity;
        float mRotation;
};

#endif
