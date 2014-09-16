#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <vector>
#include <SFML/Graphics.hpp>

class Animation
{
public:
    Animation( std::string anim );

    int addFrame( sf::Vector2f position, sf::Vector2f size );

    sf::IntRect getStartFrame() const;

    sf::IntRect getNextFrame();

    sf::IntRect getCurrentFrame() const;

    int getTimePerFrame() const;

    void setTimePerFrame( int time );

    int getNumFrames() const;

    void resetAnimation();

    bool isRepeating() const;

    void setRepeat( bool repeat );

    bool getIsDone() const;

    void setIsDone( bool isDone );

    std::string getAnimationName() const;

    void setAnimationName( std::string anim );

private:
    std::vector<sf::IntRect> mFrames;
    unsigned int mTimePerFrame;
    unsigned int mCurrentFrame;
    bool mRepeat;
    bool mIsDone;
    std::string mAnimationName;
};

#endif
