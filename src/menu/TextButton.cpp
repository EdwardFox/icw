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

    mShape.setPosition( this->getPosition() );
    mShape.setSize( this->getSize() );
    mShape.setFillColor( this->mBackgroundColor );

    sf::Vector2f textPos;
    textPos.x = this->getPosition().x + this->getSize().x / 2.f - mText.getGlobalBounds().width / 2.f;
    textPos.y = this->getPosition().y + this->getSize().y / 2.f - mText.getGlobalBounds().height / 2.f;
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

bool TextButton::onClick( Menu* menu, Game* game )
{
    if ( mClickFunction )
    {
        this->mClickFunction( menu, game );
        return true;
    }
    return false;
}
