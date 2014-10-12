#ifndef ITEM_HPP
#define ITEM_HPP

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>

class Game;

class Menu;

class Item
{
public:
    virtual ~Item() {};

    virtual void update( sf::Vector2u windowSize, sf::Time dt ) = 0;

    virtual void render( sf::RenderTarget& target, sf::Time dt ) = 0;

    virtual void onHover( Menu* menu, bool active ) = 0;

    virtual void onClick( Menu* menu, Game* game ) = 0;

    sf::Vector2f getPosition() const
    {
        return mPosition;
    }

    void setPosition( sf::Vector2f position )
    {
        mPosition = position;
    }

    sf::Vector2f getSize() const
    {
        return mSize;
    }

    void setSize( sf::Vector2f size )
    {
        mSize = size;
    }

    sf::Vector2f getOffset() const
    {
        return mOffset;
    }

    void setOffset( sf::Vector2f offset )
    {
        mOffset = offset;
    }

    float getZoom() const
    {
        return mZoom;
    }

    void setZoom( float zoom )
    {
        mZoom = zoom;
    }

    bool isVisible() const
    {
        return mVisible;
    }

    void setVisible( bool visible )
    {
        mVisible = visible;
    }

private:
    sf::Vector2f mPosition;
    sf::Vector2f mSize;
    sf::Vector2f mOffset;
    float mZoom;
    bool mVisible;
};

#endif