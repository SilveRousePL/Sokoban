#ifndef PLAYERUI_HPP_
#define PLAYERUI_HPP_

#include <SFML/Graphics.hpp>

#include "UtilityFunctions.hpp"
//#include <vector>


class PlayerUI
	:public sf::Drawable
	,public sf::Transformable
	,public sf::NonCopyable
{
public:
	PlayerUI();
	~PlayerUI();

	void SetBackground(sf::Texture & texture, sf::Vector2f position = sf::Vector2f(0,0));

	void SetObjects(sf::Texture & texture, sf::Vector2f position = sf::Vector2f(0, 0));

	void SetDisplayedObjectsCount(uint32_t value);

	void SetMaximumObjectsCount(uint32_t value);

	void SetName(std::string name);
    
    void SetFont(sf::Font & font);

	void SetMovesCounter(uint32_t value);


private:
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

private:
	uint32_t elem_count_ = 0;

	sf::Sprite background_;

	sf::Sprite objects_;
	sf::Text objects_count_;

	sf::Text name_;
	sf::Text moves_;

};

#endif //PLAYERUI_HPP_
