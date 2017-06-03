#include "PlayerUI.hpp"

PlayerUI::PlayerUI()
{
	moves_.setString("Moves: 0");
	objects_count_.setString("0");
}

PlayerUI::~PlayerUI()
{}

void PlayerUI::SetBackground(sf::Texture & texture, sf::Vector2f position)
{
	background_.setTexture(texture);
	background_.setPosition(position);
	background_.setScale(10, 1);
}

void PlayerUI::SetObjects(sf::Texture & texture, sf::Vector2f position)
{
	objects_.setTexture(texture);
	objects_.setPosition(sf::Vector2f(400, 10));
	objects_.move(position);
	objects_.setScale(0.3f, 0.5f);
}

void PlayerUI::SetDisplayedObjectsCount(uint32_t value)
{
	objects_count_.setString(UtilityFunctions::IntToString(value) + " / " + UtilityFunctions::IntToString(elem_count_));
}

void PlayerUI::SetMaximumObjectsCount(uint32_t value)
{
	elem_count_ = value;
}

void PlayerUI::SetName(std::string name)
{
	// TODO: IMPLEMENT player name
}

void PlayerUI::SetFont(sf::Font & font)
{
    name_.setFont(font);
    moves_.setFont(font);
    moves_.setCharacterSize(42);
    moves_.move(10, 0);

	objects_count_.setFont(font);
	objects_count_.setCharacterSize(42);
	objects_count_.move(430, 0);
}

void PlayerUI::SetMovesCounter(uint32_t value)
{
	moves_.setString("Moves: " + UtilityFunctions::IntToString(value));
}

void PlayerUI::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(background_, states);
	target.draw(objects_, states);

	target.draw(objects_count_, states);
	//target.draw(name_, states);
	target.draw(moves_, states);

}
