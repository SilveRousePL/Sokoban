#include "MainMenu.hpp"

#include <iostream>


MainMenu::MainMenu()
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::AddButton(sf::Texture & texture, sf::Texture & texture_click, sf::Font & font,std::string str,ButtonType type, sf::Vector2f position)
{
    buttons_.push_back(Button(texture, texture_click, font,str,type, position));
}

void MainMenu::SetLogo(sf::Texture & texture, const sf::Vector2f & position)
{
	logo_.setTexture(texture);
	logo_.setPosition(position);
}


void MainMenu::CheckPosition(sf::Vector2i mouse)
{
    for (std::vector<Button>::iterator it = buttons_.begin(); it != buttons_.end(); ++it)
    {
        if (it->getPosition().x < mouse.x && (it->getPosition().x + 200) > mouse.x && it->getPosition().y < mouse.y && it->getPosition().y + 50 > mouse.y)
            it->ChangeSprite(1);
    }
}

// HACK: add color change on button hover 

ButtonType MainMenu::CheckClick(sf::Vector2i mouse)
{
    for (std::vector<Button>::iterator it = buttons_.begin(); it != buttons_.end(); ++it)
    {
        //std::cout << "pX: " << it->getPosition().x << "\tpY: " << it->getPosition().y << std::endl;
        //std::cout << "pX: " << mouse.x << "\tpY: " << mouse.y << std::endl;

        it->ChangeSprite(0);

        if (it->getPosition().x < mouse.x && (it->getPosition().x + 200) > mouse.x && it->getPosition().y < mouse.y && it->getPosition().y + 50 > mouse.y)
        {
            return it->getType();
        }
            
            
    }
    return ButtonType::MENU_NONE;
}



void MainMenu::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    target.clear(sf::Color(0x1f, 0x1f, 0x1f, 0));
	
	target.draw(logo_,states);
    for (std::vector<Button>::const_iterator it = buttons_.begin(); it != buttons_.end(); ++it)
        target.draw(*it,states);
}
