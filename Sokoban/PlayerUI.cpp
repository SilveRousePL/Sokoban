#include "PlayerUI.hpp"


PlayerUI::PlayerUI()
{
	moves_.setString("Moves: 0");
}

PlayerUI::~PlayerUI()
{}

void PlayerUI::SetBackground(sf::Texture & texture, sf::Vector2f position)
{
	background_.setTexture(texture);
	background_.setPosition(position);
}

void PlayerUI::SetName(std::string name)
{
	// HACK: IMPLEMENT player name
}

void PlayerUI::SetFont(sf::Font & font)
{
    name_.setFont(font);
    moves_.setFont(font);
    moves_.setCharacterSize(42);
    moves_.move(10, 0);
}

void PlayerUI::SetMovesCounter(UINT32 value)
{
	moves_.setString("Moves: "+ UtilityFunctions::IntToString(value));
}

void PlayerUI::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(background_, states);
	//target.draw(name_, states);
	target.draw(moves_, states);

}
