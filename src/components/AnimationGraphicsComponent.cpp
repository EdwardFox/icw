#include <stdexcept>
#include "lib/components/AnimationGraphicsComponent.hpp"
#include "lib/GameObject.hpp"

AnimationGraphicsComponent::AnimationGraphicsComponent() :
        mTexture()
        , mSprite()
        , mAnimations()
        , mCurrentAnimation( nullptr )
        , mTimeToNextFrame( 0 )
{
    this->setType( "GraphicsComponent" );
}

void AnimationGraphicsComponent::update( GameObject& object, sf::Time dt )
{
    mSprite.setPosition( object.getPosition() );
    mSprite.setRotation( object.getRotation() );

    if ( mCurrentAnimation != nullptr )
    {
        if ( mTimeToNextFrame > mCurrentAnimation->getTimePerFrame() )
        {
            mSprite.setTextureRect( mCurrentAnimation->getNextFrame() );
            mTimeToNextFrame = 0;
        }
        else
        {
            mTimeToNextFrame += dt.asMilliseconds();
        }
    }
}

void AnimationGraphicsComponent::render( sf::RenderTarget& target, sf::Time dt ) const
{
    if ( mCurrentAnimation != nullptr )
        target.draw( mSprite );
}

void AnimationGraphicsComponent::setTexture( sf::Texture& texture )
{
    mTexture = &texture;
    mSprite.setTexture( *(mTexture) );
}

void AnimationGraphicsComponent::addAnimation( std::string key, Animation anim )
{
    mAnimations.emplace( key, anim );
}

void AnimationGraphicsComponent::setAnimation( std::string key )
{
    if ( mCurrentAnimation != nullptr )
    {
        mCurrentAnimation->resetAnimation();
    }

    try
    {
        mCurrentAnimation = &mAnimations.at( key );
        sf::IntRect frame = mCurrentAnimation->getStartFrame();
        mSprite.setTextureRect( frame );
        mSprite.setOrigin( frame.width / 2.f, frame.height / 2.f );

        mTimeToNextFrame = 0;
    }
    catch ( std::out_of_range oor )
    {
        // Animation not found
    }

}
