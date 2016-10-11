#include "Player.hpp"



Player::Player()
{
	move_count_ = 0;
}

Player::~Player()
{
}

void Player::operator=(sf::Sprite& spr)
{
	setTexture(*spr.getTexture());
}

void Player::move(sf::Vector2f & offset)
{
	setPosition(getPosition().x + offset.x, getPosition().y + offset.y);
	move_count_++;
}

unsigned int Player::GetMoveCounter() const
{
    return move_count_;
}

void Player::Reset()
{
    move_count_ = 0;
}
