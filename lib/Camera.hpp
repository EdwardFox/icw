#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <SFML/Graphics.hpp>

class GameObject;

/**
* This class defines a camera object which can be set
* to look at a fixed position or follow a target. It can
* also use a zoom factor, a lag-behind mechanic and stop
* following its target once the edges of the playable map
* have been reached.
*/
class Camera
{
public:
    /**
    * Creates the camera
    */
    Camera();

    /**
    * Updates the camera position. Will stop moving the camera
    * once we hit the edges of the playable map
    *
    * dt            - Time since last update
    * windowSize    - Size of the window in pixels
    */
    void update( sf::Time dt, sf::Vector2u windowSize );

    /**
    * Renders the camera
    */
    void render( sf::RenderTarget& target, sf::Time dt ) const;

    /**
    * Sets the target to follow and whether to initially start
    * at its location
    */
    void setFollowTarget( const GameObject* object, bool startAtTarget )
    {
        mFollowTarget = object;

        if( startAtTarget )
            mPosition = mFollowTarget->getPosition();
    }

    /**
    * Gets the offset of the camera position
    */
    sf::Vector2f getOffset() const
    {
        return mOffset;
    }

    /**
    * Sets the offset of the camera position
    */
    void setOffset( sf::Vector2f offset )
    {
        mOffset = offset;
    }

    /**
    * Gets the zoom level
    *
    * Analogous to setting the zoom level,
    * we use the reciprocal before returning
    * the zoom level, e.g. 1/x
    */
    float getZoom() const
    {
        return 1.f / mZoom;
    }

    /**
    * Sets the zoom level
    *
    * Since 1/x of the width and height are used internally
    * when zooming in (but we want the user to be able to specify
    * e.g. 2x as the zoom level) the zoom received is saved
    * as a reciprocal, e.g. 1/x.
    */
    void setZoom( float zoom )
    {
        mZoom = 1.f / zoom;
    }

    /**
    * Returns the camera position
    */
    sf::Vector2f getPosition() const
    {
        return mPosition;
    }

    /**
    * Sets the camera position
    */
    void setPosition( sf::Vector2f pos )
    {
        mPosition = pos;
    }

    /**
    * Returns the borders of the map where the camera is going to
    * stop moving.
    */
    sf::IntRect getBorders() const
    {
        return mBorders;
    }

    /**
    * Sets the borders of the map so the camera can calculate
    * where to stop following the player
    */
    void setBorders( sf::IntRect borders )
    {
        mBorders = borders;
    }

    /**
    * Returns whether the camera lags behind
    */
    bool isLaggingBehind() const
    {
        return mLagBehind;
    }

    /**
    * Sets whether the camera lags behind
    *
    * Note: Works only when following a target
    */
    void setLagBehind( bool lagBehind )
    {
        mLagBehind = lagBehind;
    }

    /**
    * Returns whether the camera stops at map borders
    */
    bool isStoppingAtBorders() const
    {
        return mStopAtBorders;
    }

    /**
    * Sets whether the camera stops at map borders
    *
    * Note: Works only when following a target
    */
    void setStopAtBorders( bool stopAtBorders )
    {
        mStopAtBorders = stopAtBorders;
    }

    /**
    * Returns the lag behind amount
    */
    float getLagBehindAmount() const
    {
        return mLagBehindAmount;
    }

    /**
    * Sets the lag behind amount
    *
    * Note: 1.0f is the highest amount possible.
    *       The bigger the amount, the faster the camera
    *       follows behind.
    */
    void setLagBehindAmount( float lagBehindAmount )
    {
        mLagBehindAmount = lagBehindAmount;
    }

private:
    /**
    * Stores a pointer to the game object to follow
    */
    const GameObject* mFollowTarget;

    /**
    * Stores the offset to the camera position
    */
    sf::Vector2f mOffset;

    /**
    * Stores the camera zoom
    */
    float mZoom;

    /**
    * Stores the camera position
    */
    sf::Vector2f mPosition;

    /**
    * Stores the worlds borders
    */
    sf::IntRect mBorders;

    /**
    * Stores whether to lag behind
    */
    bool mLagBehind;

    /**
    * Stores whether to stop at borders
    */
    bool mStopAtBorders;

    /**
    * Stores the lag behind amount
    */
    float mLagBehindAmount;
};

#endif