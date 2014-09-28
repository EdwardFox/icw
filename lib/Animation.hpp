#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <vector>
#include <SFML/Graphics.hpp>

/**
* This class stores animation properties and provides
* an interface to manipulate and play the stored animation.
* It does not store any textures or images directly. Instead
* it keeps track of the area that defines a part of the textures
* to enable usage of spritesheets. It also provides methods
* to play the animation as well as keeping track of its state
* (e.g. finished, can be repeated, and so on).
*
* The animation has no idea which spritesheet it belongs to, this
* is supposed to be handled by the graphics component.
*/
class Animation
{
public:
    /**
    * Creates a new animation
    *
    * std::string anim - The animation name
    */
    Animation( std::string anim );

    /**
    * Adds a frame to the animation
    *
    * sf::Vector2f position - The position of the texture in the spritesheet
    * sf::Vector2f size     - The size of the texture in the spritesheet
    *
    * return - The index of the newly added frame
    */
    int addFrame( sf::Vector2f position, sf::Vector2f size );

    /**
    * Returns the first frame defined for this animation
    */
    sf::IntRect getStartFrame() const;

    /**
    * Returns the position and size for the current frame
    */
    sf::IntRect getCurrentFrame() const;

    /**
    * Advances the index of the current frame to the next one,
    * or jumps back to index 0 if the animation is at its last frame
    * and repeatable. Then returns the position and size of for the
    * texture.
    */
    sf::IntRect getNextFrame();

    /**
    * Resets the index to 0 and is done to false
    */
    void resetAnimation();

    /**
    * Returns the time each frame is displayed in milliseconds
    */
    int getTimePerFrame() const
    {
        return mTimePerFrame;
    }

    /**
    * Sets the time each frame is display in milliseconds
    */
    void setTimePerFrame( int time )
    {
        mTimePerFrame = time;
    }

    /**
    * Returns the amount of frames stored
    */
    int getNumFrames() const
    {
        return mFrames.size();
    }

    /**
    * Gets whether the animation is repeatable or not
    */
    bool isRepeatable() const
    {
        return mRepeatable;
    }

    /**
    * Sets whether the animation is repeatable or not
    */
    void setRepeatable( bool repeat )
    {
        mRepeatable = repeat;
    }

    /**
    * Returns whether the animation ran completely
    */
    bool isFinished() const
    {
        return mFinished;
    }

    /**
    * Sets whether the animation ran completely
    */
    void setFinished( bool isDone )
    {
        mFinished = isDone;
    }

    /**
    * Returns the name of the animation
    */
    std::string getAnimationName() const
    {
        return mAnimationName;
    }

    /**
    * Sets the name of the animation
    */
    void setAnimationName( std::string anim )
    {
        mAnimationName = anim;
    }

private:
    /**
    * Stores frames by position and size relative to a spritesheet
    */
    std::vector<sf::IntRect> mFrames;

    /**
    * Stores the time each frame is displayed
    */
    unsigned int mTimePerFrame;

    /**
    * Stores the index of the current frame
    */
    unsigned int mCurrentFrame;

    /**
    * Stores whether the animation is repeatable
    */
    bool mRepeatable;

    /**
    * Stores whether the animation has finished playing
    */
    bool mFinished;

    /**
    * Stores the animation name
    */
    std::string mAnimationName;
};

#endif
