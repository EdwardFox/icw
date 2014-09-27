#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <memory>
#include <string>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "lib/Data.hpp"
#include "lib/interfaces/IGraphicsComponent.hpp"

class World;

class IContactable;

class GameObject
{
public:
    GameObject( World* world, std::string name );

    virtual ~GameObject() {};

    virtual void attachComponent( std::string key, IComponent* component );

    virtual void detachComponent( std::string key );

    virtual IComponent* const getComponent( std::string key ) const;

    virtual void setGraphicComponent( IGraphicsComponent* component );

    virtual IGraphicsComponent* const getGraphicComponent() const;

    virtual void update( sf::Time dt );

    virtual void render( sf::RenderTarget& target, sf::Time dt ) const;

    virtual void onHit( GameObject* hitBy, Contact contact );

    virtual sf::Vector2f getPosition() const
    {
        return mPosition;
    }

    virtual void setPosition( sf::Vector2f position )
    {
        mPosition = position;
    }

    virtual sf::Vector2f getSize() const
    {
        return mSize;
    }

    virtual void setSize( sf::Vector2f size )
    {
        mSize = size;
    }

    virtual float getRotation() const
    {
        return mRotation;
    }

    virtual void setRotation( float rotation )
    {
        mRotation = rotation;
    }

    virtual bool isExpired() const
    {
        return mExpired;
    }

    virtual void setExpired( bool expired )
    {
        mExpired = expired;
    }

    virtual World* getWorld()
    {
        return mWorld;
    }

    std::string getName() const
    {
        return mName;
    }

    void setMName( std::string name )
    {
        GameObject::mName = name;
    }

private:

    World* mWorld;
    std::unordered_map<std::string, std::unique_ptr<IComponent>> mComponents;
    std::unique_ptr<IGraphicsComponent> mGraphicComponent;
    sf::Vector2f mPosition;
    sf::Vector2f mSize;
    sf::Vector2f mVelocity;
    bool mExpired;
    float mRotation;
    std::string mName;
};

#endif
