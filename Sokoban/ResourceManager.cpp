#include "ResourceManager.hpp"
#include <Windows.h>

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

/*
    //TODO:
    Mo¿e przeniosê tutaj loading textur, a w GameMap inaczej u³o¿ê inicjalizacjê (przeniosê do konstruktora)
*/

bool ResourceManager::LoadTexture(TEXTURE_ID id, const std::string file_path)
{
		std::shared_ptr<sf::Texture> tex_(new sf::Texture());
		if (!tex_->loadFromFile(file_path))
			return false;
        tex_->setSmooth(true);
		texture_holder_.insert(std::make_pair(id, std::move(tex_)));
		return true;
}

bool ResourceManager::LoadFont(std::string font_path)
{
	return font_holder_.loadFromFile(font_path);
}

std::shared_ptr<sf::Texture> const ResourceManager::GetTexture(TEXTURE_ID id) const
{
	return texture_holder_.at(id);
}

sf::Sprite const ResourceManager::GetSprite(TEXTURE_ID id) const
{
	sf::Sprite spr_;
	spr_.setTexture(*texture_holder_.at(id));
	return spr_;
}

sf::Font & ResourceManager::GetFont()
{
    return font_holder_;
}
