#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <SFML/Graphics.hpp>

class Player
	:public sf::Sprite
{
public:
	// default constructor and destructor
	Player();
	~Player();

	void operator=(sf::Sprite& spr);

	////////////////////////////////////////
	/// \brief Moves player through offset
	////////////////////////////////////////
	void move(sf::Vector2f& offset);

	////////////////////////////////////////
	/// \returns Player's move counter
	////////////////////////////////////////
    unsigned int GetMoveCounter() const;

	////////////////////////////////////////
	/// \returns Reset player's move counter
	////////////////////////////////////////
    void Reset();

private:
	unsigned int move_count_; // For UI
};

#endif // !PLAYER_HPP_
