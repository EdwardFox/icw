#include "lib/Animation.hpp"

Animation::Animation( std::string anim ) :
        mFrames()
        , mTimePerFrame( 0 )
        , mCurrentFrame( 0 )
        , mRepeatable( true )
        , mFinished( false )
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
        if ( mRepeatable )
        {
            mCurrentFrame = 0;
        }
        else
        {
            mFinished = true;
        }
    }
    else
    {
        ++mCurrentFrame;
    }

    return mFrames.at( mCurrentFrame );
}

void Animation::resetAnimation()
{
    mCurrentFrame = 0;
    mFinished = false;
}
