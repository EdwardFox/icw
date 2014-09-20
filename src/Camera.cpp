#include <lib/GameObject.hpp>
#include "lib/Camera.hpp"

Camera::Camera() :
        mFollowTarget( nullptr )
        , mOffset( 0.f, 0.f )
        , mZoom( 1.f )
        , mLag( 0.f, 0.f )
        , mBorders( 0.f, 0.f, 0.f, 0.f )
{

}

void Camera::update( sf::Time dt, sf::Vector2u windowSize )
{
    // Low pass filter to make the camera lag behind
    // @see: http://stackoverflow.com/questions/6176207/implementing-a-rubberbanding-camera-using-canvas-transformations-in-android
    if ( mFollowTarget )
    {
        int leftBorder = mFollowTarget->getPosition().x - windowSize.x / (2 * this->getZoom());
        int rightBorder = mFollowTarget->getPosition().x + windowSize.x / (2 * this->getZoom());
        int bottomBorder = mFollowTarget->getPosition().y + windowSize.y / (2 * this->getZoom()) + mOffset.y + 8.f; // TODO: Figure out why the 8.f are needed
        int topBorder = mFollowTarget->getPosition().y - windowSize.y / (2* this->getZoom() );
        float t = 0.2f;

        if ( leftBorder > mBorders.left && rightBorder < mBorders.width )
            mLag.x = mLag.x * (1.f - t) + (mFollowTarget->getPosition().x) * t;

        if ( topBorder > mBorders.top && bottomBorder < mBorders.height )
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
        view.setCenter( mLag.x + mOffset.x, mLag.y + mOffset.y );
    }

    target.setView( view );
}

void Camera::setFollowTarget( GameObject* object )
{
    mFollowTarget = object;
    mLag = mFollowTarget->getPosition();
}

sf::Vector2f Camera::getOffset() const
{
    return mOffset;
}

void Camera::setOffset( sf::Vector2f offset )
{
    mOffset = offset;
}

float Camera::getZoom() const
{
    return 1.f / mZoom;
}

void Camera::setZoom( float zoom )
{
    mZoom = 1.f / zoom;
}

sf::Vector2f Camera::getPosition() const
{
    return mLag;
}

sf::IntRect Camera::getBorders() const
{
    return mBorders;
}

void Camera::setBorders( sf::IntRect borders )
{
    mBorders = borders;
}
