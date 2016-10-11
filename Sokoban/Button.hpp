#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include <SFML/Graphics.hpp>
#include <string>
#include "ButtonType.h"

class Button
    :public sf::Drawable
    ,public sf::Transformable
{
public:
    Button(sf::Texture & texture, sf::Texture & texture_click, sf::Font & font, std::string str,ButtonType type,sf::Vector2f position = sf::Vector2f(0,0));
    ~Button();

    void OnHover();

    void SetBackground(sf::Texture & texture, sf::Vector2f position = sf::Vector2f(0, 0));

    void ChangeSprite(bool b);

    void SetFont(sf::Font & font);

    ButtonType getType() const;

private:
    bool isActive_;
    sf::Text btn_text_;
    sf::Sprite btn_bg_;
    sf::Sprite btn_bg_active_;
    ButtonType btn_type_;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};


#endif // !BUTTON_HPP_

