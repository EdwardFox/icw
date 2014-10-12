#include <lib/menu/Menu.hpp>
#include "lib/menu/TextButton.hpp"

TextButton::TextButton() :
        mFont()
        , mText()
        , mTextColor()
        , mHighlightTextColor()
        , mBackgroundColor()
        , mShape()
        , mClickFunction()
        , mHighlighted( false )
{
    mText.setScale( 0.33f, 0.33f );
}

void TextButton::update( sf::Vector2u windowSize, sf::Time dt )
{
    if( this->isHighlighted() )
    {
        mText.setColor( mHighlightTextColor );
    }
    else
    {
        mText.setColor( mTextColor );
    }

    sf::Vector2f window( windowSize.x, windowSize.y );
    sf::Vector2f basePos = this->getPosition() + this->getOffset() - (window / 2.f) / this->getZoom();

    mShape.setPosition( basePos );
    mShape.setSize( this->getSize() );
    mShape.setFillColor( this->mBackgroundColor );

    sf::Vector2f textPos;
    textPos.x = basePos.x + this->getSize().x / 2.f - mText.getGlobalBounds().width / 2.f;
    textPos.y = basePos.y + this->getSize().y / 2.f - mText.getGlobalBounds().height / 2.f;
    mText.setPosition( textPos );
}

void TextButton::render( sf::RenderTarget& target, sf::Time dt )
{
    target.draw( mShape );
    target.draw( mText );
}

void TextButton::onHover( Menu* menu, bool active )
{
    if( active )
    {
        mHighlighted = true;
    }
    else
    {
        mHighlighted = false;
    }

}

void TextButton::onClick( Menu* menu, Game* game )
{
    if ( mClickFunction )
    {
        this->mClickFunction( menu, game );
    }
}
