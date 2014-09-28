#include <lib/GameObject.hpp>
#include "lib/Camera.hpp"

Camera::Camera() :
        mFollowTarget( nullptr )
        , mOffset( 0.f, 0.f )
        , mZoom( 1.f )
        , mPosition( 0.f, 0.f )
        , mBorders( 0.f, 0.f, 0.f, 0.f )
        , mLagBehind( true )
        , mStopAtBorders( true )
        , mLagBehindAmount( 0.2f )
{

}

void Camera::update( sf::Time dt, sf::Vector2u windowSize )
{
    if ( mFollowTarget )
    {
        int leftBorder = mFollowTarget->getPosition().x - windowSize.x / (2 * this->getZoom());
        int rightBorder = mFollowTarget->getPosition().x + windowSize.x / (2 * this->getZoom());
        int bottomBorder = mFollowTarget->getPosition().y + windowSize.y / (2 * this->getZoom()) + mOffset.y + 8.f; // TODO: Figure out why the 8.f are needed
        int topBorder = mFollowTarget->getPosition().y - windowSize.y / (2* this->getZoom() );

        if( mLagBehind )
        {
            if( mStopAtBorders )
            {
                if ( leftBorder > mBorders.left && rightBorder < mBorders.width )
                    mPosition.x = mPosition.x * (1.f - mLagBehindAmount) + (mFollowTarget->getPosition().x) * mLagBehindAmount;

                if ( topBorder > mBorders.top && bottomBorder < mBorders.height )
                    mPosition.y = mPosition.y * (1.f - mLagBehindAmount) + (mFollowTarget->getPosition().y) * mLagBehindAmount;
            }
            else
            {
                // Low pass filter to make the camera lag behind
                // @see: http://stackoverflow.com/questions/6176207/implementing-a-rubberbanding-camera-using-canvas-transformations-in-android
                mPosition.x = mPosition.x * (1.f - mLagBehindAmount) + (mFollowTarget->getPosition().x) * mLagBehindAmount;
                mPosition.y = mPosition.y * (1.f - mLagBehindAmount) + (mFollowTarget->getPosition().y) * mLagBehindAmount;
            }

        }
        else
        {
            if( mStopAtBorders )
            {
                if ( leftBorder > mBorders.left && rightBorder < mBorders.width )
                    mPosition.x = mFollowTarget->getPosition().x;

                if ( topBorder > mBorders.top && bottomBorder < mBorders.height )
                    mPosition.y = mFollowTarget->getPosition().y;
            }
            else
            {
                mPosition = mFollowTarget->getPosition();
            }
        }
    }
}

void Camera::render( sf::RenderTarget& target, sf::Time dt ) const
{
    float width = target.getSize().x * mZoom;
    float height = target.getSize().y * mZoom;
    sf::View view( sf::FloatRect( mOffset.x, mOffset.y, width, height ) );
    view.setCenter( mPosition.x + mOffset.x, mPosition.y + mOffset.y );

    target.setView( view );
}
