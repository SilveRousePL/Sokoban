#ifndef MAINMENU_HPP_
#define MAINMENU_HPP_

#include <SFML/Graphics.hpp>
#include <vector>

#include "Button.hpp"
#include "ButtonType.h"

class MainMenu
    :public sf::Drawable
    , public sf::NonCopyable
{
public:
    MainMenu(); 
    ~MainMenu();


    void AddButton(sf::Texture & texture, sf::Texture & texture_click, sf::Font & font, std::string str, ButtonType type, sf::Vector2f position = sf::Vector2f(0, 0));

	void SetLogo(sf::Texture & texture,const sf::Vector2f & position);

    void CheckPosition(sf::Vector2i mouse);
    
    ButtonType CheckClick(sf::Vector2i mouse);
private:
    std::vector<Button> buttons_;

	sf::Sprite logo_;

private:

    // Inherited via Drawable
    virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

};

#endif // MAINMENU_HPP_