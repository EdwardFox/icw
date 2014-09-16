#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <SFML/Graphics.hpp>

class GameObject;

class Camera
{
public:
    Camera();

    void update( sf::Time dt );

    void render( sf::RenderTarget& target, sf::Time dt ) const;

    void setFollowTarget( GameObject* object )
    {
        mFollowTarget = object;
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
        mZoom = 1.f / zoom;
    }

private:
    GameObject* mFollowTarget;
    sf::Vector2f mOffset;
    float mZoom;
    sf::Vector2f mLag;
};

#endif