#ifndef RESOURCEMANAGER_HPP_
#define RESOURCEMANAGER_HPP_

#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
#include <string>

#include <iostream>

#include "ResourceType.h"

///\brief Class for resource management
class ResourceManager 
{
public:
	// default constructor and destructor
	ResourceManager();
	~ResourceManager();

	////////////////////////////////////////
	/// \brief Loads texture from file
	/// \returns is loaded successfully
	////////////////////////////////////////
	bool LoadTexture(TEXTURE_ID id, const std::string file_path);

	////////////////////////////////////////
	/// \brief Loads font from file
	/// \returns is loaded successfully
	////////////////////////////////////////
	bool LoadFont(std::string font_path);

	////////////////////////////////////////
	/// \brief Loads font from file
	/// \returns shared pointer to texture
	////////////////////////////////////////
	std::shared_ptr<sf::Texture> const GetTexture(TEXTURE_ID id) const;
	
	////////////////////////////////////////
	/// \brief Create new sprite with sended texture
	/// \returns shared pointer to texture
	////////////////////////////////////////
	sf::Sprite const GetSprite(TEXTURE_ID  id) const;

	sf::Font & GetFont();


private:
	//dictionary
	std::map<TEXTURE_ID, std::shared_ptr<sf::Texture>> texture_holder_;
	sf::Font font_holder_; 

};

#endif //RESOURCEMANAGER_HPP_