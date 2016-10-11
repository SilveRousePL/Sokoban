#ifndef GAMEMAP_HPP_
#define GAMEMAP_HPP_

#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <memory>
#include <vector>

#include "ResourceManager.hpp"
#include "Artifact.hpp"
#include "Player.hpp"
#include "UtilityFunctions.hpp"
#include "MapGen.hpp"

class GameMap
	:public sf::Drawable
	,public sf::Transformable
{
public:
	////////////////////////////////////////
	/// \brief Contructor for new game map
	/// \param: reference to ResourceManager
	////////////////////////////////////////
    GameMap(ResourceManager & r);

	////////////////////////////////////////
	/// \brief Destructor (delete pointer)
	////////////////////////////////////////
    ~GameMap();

	////////////////////////////////////////
	/// \brief Loads map
	/// \param level	Map id
	////////////////////////////////////////
    bool LoadMap(unsigned int level = 1);

	////////////////////////////////////////
	/// \brief Prints map to console
	///	This is debug only function, for check map correctness
	/// \param level	Map id
	////////////////////////////////////////
	void PrintToConsole();

	////////////////////////////////////////
	/// \brief Returns ID of map element in given position
	/// \param pos sf::Vector2f
	/// \returns ID of MAP_ELEMENT
	/// \see MAP_ELEMENT
	////////////////////////////////////////
	int GetMapElementId (sf::Vector2f pos) const;

	////////////////////////////////////////
	/// \brief Used to get position of player spawner
	/// \returns position of player spawner
	////////////////////////////////////////
	sf::Vector2f GetSpawnPosition() const;

    ////////////////////////////////////////
    /// \brief Used to get width of map
    /// \returns count of width tiles
    ////////////////////////////////////////
    const int& GetMapWidth() const;

	////////////////////////////////////////
	/// \brief Used to get width of map
	/// \returns count of width tiles
	////////////////////////////////////////
    const int& GetMapHeight() const;

	////////////////////////////////////////
	/// \returns Can element run
	////////////////////////////////////////
    bool CheckCollision(sf::Vector2f pos, sf::Vector2f oryginal_pos, sf::Vector2f offset);

	////////////////////////////////////////
	/// \brief Moves player through offset
	////////////////////////////////////////
    void MovePlayer(sf::Vector2f offset);

	////////////////////////////////////////
	/// \returns Player's position on the map
	////////////////////////////////////////
    sf::Vector2f GetPlayerPosition() const;

	////////////////////////////////////////
	/// \returns If all artifacts collected
	////////////////////////////////////////
    bool CheckArtifacts();

    UINT32 GetPlayerMoves();

    void ResetPlayer();

	

private:
	////////////////////////////////////////
	/// \brief Draws element
	/// Inherited by sf::Drawable
	////////////////////////////////////////
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	////////////////////////////////////////
	/// \brief Initialize player object
	////////////////////////////////////////
	void InitializePlayer();

	////////////////////////////////////////
	/// \brief Clears map
	////////////////////////////////////////
	void WipeMap();

private:
    static const int map_size_x_ = 32;								///< defines map width
	static const int map_size_y_ = 16;								///< defines map height
	int ground_id_map_[map_size_y_][map_size_x_];					///< declaration of map table
    ResourceManager* ptr_manager_;									///< declaration of pointer to ResourceManager (for gettin' sprites)
	sf::Vector2f spawn_position_;									///< player spawn_position

    Player player_;													///< player object
    std::vector<Artifact> artifacts_;                               ///< artifact vector

    unsigned int trigger_count_;									///< artifacts counter
};

#endif //MAP_HPP_