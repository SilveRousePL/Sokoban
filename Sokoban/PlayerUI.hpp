#ifndef PLAYERUI_HPP_
#define PLAYERUI_HPP_

#include <SFML/Graphics.hpp>

#include "UtilityFunctions.hpp"
//#include <vector>

#define UINT32 unsigned int

class PlayerUI
	:public sf::Drawable
	,public sf::Transformable
	,public sf::NonCopyable
{
public:
	PlayerUI();
	~PlayerUI();

	void SetBackground(sf::Texture & texture, sf::Vector2f position = sf::Vector2f(0,0));

	void SetName(std::string name);
    
    void SetFont(sf::Font & font);

	void SetMovesCounter(UINT32 value);


private:
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

private:
	sf::Sprite background_;
	sf::Text name_;
	sf::Text moves_;

};

#endif //PLAYERUI_HPP_
