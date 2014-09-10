#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <vector>
#include <SFML/Graphics.hpp>

class Animation
{
public:
    Animation();

    int addFrame( sf::Vector2f position, sf::Vector2f size );

    sf::IntRect getStartFrame() const;

    sf::IntRect getNextFrame();

    sf::IntRect getCurrentFrame() const;

    int getTimePerFrame() const;

    void setTimePerFrame( int time );

    int getNumFrames() const;

    void resetAnimation();

private:
    std::vector<sf::IntRect> mFrames;
    unsigned int mTimePerFrame;
    unsigned int mCurrentFrame;
};

#endif
