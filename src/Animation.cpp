#include "lib/Animation.hpp"

Animation::Animation() :
        mFrames()
        , mTimePerFrame(0)
        , mCurrentFrame(0)
{

}

int Animation::addFrame( sf::Vector2f position, sf::Vector2f size )
{
    sf::IntRect rect(position.x, position.y, size.x, size.y);
    mFrames.push_back(rect);

    return mFrames.size() -1;
}

sf::IntRect Animation::getStartFrame() const
{
    return mFrames.at(0);
}

sf::IntRect Animation::getCurrentFrame() const
{
    return mFrames.at(mCurrentFrame);
}

sf::IntRect Animation::getNextFrame()
{
    if( mCurrentFrame == mFrames.size()-1 )
    {
        mCurrentFrame = 0;
    }
    else
    {
        ++mCurrentFrame;
    }

    return mFrames.at(mCurrentFrame);
}

int Animation::getTimePerFrame() const
{
    return mTimePerFrame;
}

void Animation::setTimePerFrame(int time)
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
}
