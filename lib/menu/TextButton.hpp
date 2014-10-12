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

    virtual void onHover( Menu* menu ) override;

    virtual void onClick( Menu* menu, Game* game ) override;

    sf::Font const getFont() const
    {
        return mFont;
    }

    void setFont( sf::Font const font )
    {
        mFont = font;
        mText.setFont( mFont );
    }

    sf::Text const getText() const
    {
        return mText;
    }

    void setText( sf::Text const text )
    {
        mText = text;
    }

    sf::Color const getBackgroundColor() const
    {
        return mBackgroundColor;
    }

    void setBackgroundColor( sf::Color const backgroundColor )
    {
        mBackgroundColor = backgroundColor;
    }

    void setClickFunction( std::function<void(Menu*, Game*)> clickFunction )
    {
        mClickFunction = clickFunction;
    }

private:
    sf::Font mFont;
    sf::Text mText;
    sf::Color mBackgroundColor;
    sf::RectangleShape mShape;
    std::function<void( Menu* menu, Game* game )> mClickFunction;
};

#endif