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

    void setFollowTarget( GameObject* object );

    sf::Vector2f getOffset() const;

    void setOffset( sf::Vector2f offset );

    float getZoom() const;

    void setZoom( float zoom );

    sf::Vector2f getPosition() const;

private:
    GameObject* mFollowTarget;
    sf::Vector2f mOffset;
    float mZoom;
    sf::Vector2f mLag;
};

#endif