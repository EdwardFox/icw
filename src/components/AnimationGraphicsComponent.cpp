#include <stdexcept>
#include "lib/components/AnimationGraphicsComponent.hpp"
#include "lib/gameobjects/GameObject.hpp"

AnimationGraphicsComponent::AnimationGraphicsComponent( GameObject* gameObject ) :
        mTexture()
        , mGameObject( gameObject )
        , mSprite()
        , mAnimations()
        , mCurrentAnimation( nullptr )
        , mTimeToNextFrame( 0 )
        , mHightlightColor( sf::Color::Red )
        , mHighlightTimer()
        , mHighlightTime( 75.f )
{
    this->setType( "GraphicsComponent" );
}

void AnimationGraphicsComponent::update( GameObject* object, sf::Time dt )
{
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

    /**
    * Origin x: Centered on objects width to allow for wider frames
    * Origin y: At the bottom of the frame, to always align the bottom
    *           of each frame at the ground, allowing for bumps in the
    *           animation
    *
    * Finally adjust the sprite position to align with the new origin
    */
    mSprite.setOrigin( object->getSize().x/2.f, mCurrentAnimation->getCurrentFrame().height );
    sf::Vector2f pos = object->getPosition();
    pos.y += mCurrentAnimation->getCurrentFrame().height/2.f;

    mSprite.setPosition( pos );
    mSprite.setRotation( object->getRotation() );

    /** Highlight **/
    if( mHighlightTimer.getElapsedTime().asMilliseconds() < mHighlightTime )
        mSprite.setColor( mHightlightColor );
    else
        mSprite.setColor( sf::Color::White );
}

void AnimationGraphicsComponent::render( sf::RenderTarget& target, sf::Time dt ) const
{
    if ( mCurrentAnimation != nullptr )
    {
        target.draw( mSprite );
    }
}

void AnimationGraphicsComponent::setTexture( sf::Texture* texture )
{
    mTexture = texture;
    mSprite.setTexture( *(mTexture) );
}

void AnimationGraphicsComponent::addAnimation( std::string key, Animation anim )
{
    mAnimations.emplace( key, anim );
}

void AnimationGraphicsComponent::setAnimation( std::string key )
{
    if ( mCurrentAnimation )
    {
        // Only set a new animation if it is different from the current one
        if ( key != mCurrentAnimation->getAnimationName() )
        {
            mCurrentAnimation->resetAnimation();
            try
            {
                mCurrentAnimation = &mAnimations.at( key );
                sf::IntRect frame = mCurrentAnimation->getCurrentFrame();
                mSprite.setTextureRect( frame );

                mTimeToNextFrame = 0;
            }
            catch ( std::out_of_range oor )
            {
                // Animation not found
            }
        }
    }
    else    // Set initial animation
    {
        try
        {
            mCurrentAnimation = &mAnimations.at( key );
            sf::IntRect frame = mCurrentAnimation->getStartFrame();
            mSprite.setTextureRect( frame );

            mTimeToNextFrame = 0;
        }
        catch ( std::out_of_range oor )
        {
            // Animation not found
        }
    }
}

sf::Vector2f AnimationGraphicsComponent::getFlipped() const
{
    return mSprite.getScale();
}

void AnimationGraphicsComponent::setFlipped( sf::Vector2f flip )
{
    mSprite.setScale( flip.x, flip.y );
}

void AnimationGraphicsComponent::resetCurrentAnimation()
{
    mCurrentAnimation->resetAnimation();
}

bool AnimationGraphicsComponent::isAnimationFinished() const
{
    return mCurrentAnimation->isFinished();
}

GameObject* AnimationGraphicsComponent::getGameObject() const
{
    return mGameObject;
}

void AnimationGraphicsComponent::highlight()
{
    mHighlightTimer.restart();
}
