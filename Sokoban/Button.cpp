#include "Button.hpp"


Button::Button(sf::Texture & texture, sf::Texture & texture_click, sf::Font & font, std::string str, ButtonType type, sf::Vector2f position)
{
    // HACK: Button size 
    isActive_ = false;

    btn_type_ = type;

    btn_bg_.setTexture(texture);
    btn_bg_.setPosition(position);

    btn_bg_active_.setTexture(texture_click);
    btn_bg_active_.setPosition(position);

    btn_text_.setPosition(position);

    btn_text_.setFont(font);
    btn_text_.setColor(sf::Color(0x66, 0x66, 0x66, 255));
    btn_text_.move(10, 0);

    btn_text_.setString(str);

    setPosition(position);
}

Button::~Button()
{

}

void Button::OnHover()
{
    btn_text_.setColor(sf::Color::Yellow);
}

ButtonType Button::getType() const
{
    return btn_type_;
}

void Button::SetBackground(sf::Texture & texture, sf::Vector2f position)
{
    btn_bg_.setTexture(texture);
    btn_bg_.setPosition(position);
}

void Button::ChangeSprite(bool b)
{
    isActive_ = b;
    /*(isActive_) ? isActive_ = false : isActive_ = true;*/
}

// HACK: TEXT POSITIONING!
void Button::SetFont(sf::Font & font)
{
    btn_text_.setFont(font);
    btn_text_.setColor(sf::Color(0x66, 0x66, 0x66, 255));
    btn_text_.move(10, 0);
}



void Button::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    
    (!isActive_) ? target.draw(btn_bg_) : target.draw(btn_bg_active_);

    target.draw(btn_text_);
}
