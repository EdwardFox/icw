#ifndef TEXT_BUTTON_HPP
#define TEXT_BUTTON_HPP

#include <lib/Game.hpp>
#include "lib/menu/Item.hpp"
#include "Menu.hpp"

class TextButton : public Item
{
public:
    TextButton();

    virtual ~TextButton()
    {
    };

    virtual void update( sf::Vector2u windowSize, sf::Time dt ) override;

    virtual void render( sf::RenderTarget& target, sf::Time dt ) override;

    virtual void onHover( Menu* menu, bool active ) override;

    virtual void onClick( Menu* menu, Game* game ) override;

    sf::Font const getFont() const
    {
        return mFont;
    }

    void setFont( std::string font )
    {
        mFont.loadFromFile( font );
        mText.setFont( mFont );
    }

    sf::Text const getText() const
    {
        return mText;
    }

    void setText( std::string text )
    {
        mText.setString( text );
    }

    sf::Color const getBackgroundColor() const
    {
        return mBackgroundColor;
    }

    void setBackgroundColor( sf::Color const backgroundColor )
    {
        mBackgroundColor = backgroundColor;
    }

    void setTextColor( sf::Color const color )
    {
        mText.setColor( color );
        mTextColor = color;
    }

    void setHighlightTextColor( sf::Color const color )
    {
        mHighlightTextColor = color;
    }

    void setClickFunction( std::function<void(Menu*, Game*)> clickFunction )
    {
        mClickFunction = clickFunction;
    }

    bool isHighlighted() const
    {
        return mHighlighted;
    }

    void setHighlighted( bool highlighted )
    {
        mHighlighted = highlighted;
    }

private:
    sf::Font mFont;
    sf::Text mText;
    sf::Color mTextColor;
    sf::Color mHighlightTextColor;
    sf::Color mBackgroundColor;
    sf::RectangleShape mShape;
    std::function<void( Menu* menu, Game* game )> mClickFunction;
    bool mHighlighted;
};

#endif