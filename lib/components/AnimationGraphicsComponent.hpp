#ifndef ANIMATION_GRAPHICS_COMPONENT_HPP
#define ANIMATION_GRAPHICS_COMPONENT_HPP

#include <unordered_map>
#include <string>
#include "lib/interfaces/IGraphicsComponent.hpp"
#include "lib/Animation.hpp"

class AnimationGraphicsComponent : public IGraphicsComponent
{
public:
    AnimationGraphicsComponent();

    virtual void update( GameObject& object, sf::Time dt );

    virtual void render( sf::RenderTarget& target, sf::Time dt ) const;

    void setTexture( sf::Texture& texture );

    void addAnimation( std::string key, Animation anim );

    void setAnimation( std::string key );

    sf::Vector2f getFlipped() const;

    void setFlipped( sf::Vector2f flip );

    void resetCurrentAnimation();

    bool isAnimationFinished() const;

private:
    sf::Texture* mTexture;
    sf::Sprite mSprite;
    std::unordered_map<std::string, Animation> mAnimations;
    Animation* mCurrentAnimation;
    int mTimeToNextFrame;
};

#endif
