#include "lib/Animation.hpp"

Animation::Animation( std::string anim ) :
        mFrames()
        , mTimePerFrame( 0 )
        , mCurrentFrame( 0 )
        , mRepeat( true )
        , mIsDone( false )
        , mAnimationName( anim )
{

}

int Animation::addFrame( sf::Vector2f position, sf::Vector2f size )
{
    sf::IntRect rect( position.x, position.y, size.x, size.y );
    mFrames.push_back( rect );

    return mFrames.size() - 1;
}

sf::IntRect Animation::getStartFrame() const
{
    return mFrames.at( 0 );
}

sf::IntRect Animation::getCurrentFrame() const
{
    return mFrames.at( mCurrentFrame );
}

sf::IntRect Animation::getNextFrame()
{
    if ( mCurrentFrame == mFrames.size() - 1 )
    {
        if ( mRepeat )
        {
            mCurrentFrame = 0;
        }
        else
        {
            mIsDone = true;
        }
    }
    else
    {
        ++mCurrentFrame;
    }

    return mFrames.at( mCurrentFrame );
}

int Animation::getTimePerFrame() const
{
    return mTimePerFrame;
}

void Animation::setTimePerFrame( int time )
{
    mTimePerFrame = time;
}

int Animation::getNumFrames() const
{
    return mFrames.size();
}

void Animation::resetAnimation()
{
    mCurrentFrame = 0;
    mIsDone = false;
}

bool Animation::isRepeating() const
{
    return mRepeat;
}

void Animation::setRepeat( bool repeat )
{
    mRepeat = repeat;
}

bool Animation::getIsDone() const
{
    return mIsDone;
}

void Animation::setIsDone( bool isDone )
{
    mIsDone = isDone;
}

std::string Animation::getAnimationName() const
{
    return mAnimationName;
}

void Animation::setAnimationName( std::string anim )
{
    mAnimationName = anim;
}
