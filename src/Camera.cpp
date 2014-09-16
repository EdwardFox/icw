#include <lib/GameObject.hpp>
#include "lib/Camera.hpp"

Camera::Camera() :
        mFollowTarget( nullptr )
        , mOffset( 0.f, 0.f )
        , mZoom( 1.f )
        , mLag( 0.f, 0.f )
{

}

void Camera::update( sf::Time dt )
{
    // Low pass filter to make the camera lag behind
    // @see: http://stackoverflow.com/questions/6176207/implementing-a-rubberbanding-camera-using-canvas-transformations-in-android
    if ( mFollowTarget )
    {
        float t = 0.1f;
        mLag.x = mLag.x * (1.f - t) + (mFollowTarget->getPosition().x) * t;
        mLag.y = mLag.y * (1.f - t) + (mFollowTarget->getPosition().y) * t;
    }
}

void Camera::render( sf::RenderTarget& target, sf::Time dt ) const
{
    float width = target.getSize().x * mZoom;
    float height = target.getSize().y * mZoom;
    sf::View view( sf::FloatRect( mOffset.x, mOffset.y, width, height ) );

    if ( mFollowTarget )
    {
        view.setCenter( mLag.x, mLag.y - 25.f );
    }

    target.setView( view );
}
