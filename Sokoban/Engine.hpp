
#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Windows.h>

#include <iostream>
#include <string>
#include <cstdint>

#include "ResourceManager.hpp"
#include "GameMap.hpp"
#include "PlayerUI.hpp"
#include "GameState.h"
#include "MainMenu.hpp"

////////////////////////////////////////
/// \brief Main class - engine framework
////////////////////////////////////////
class Engine
{
public:
	////////////////////////////////////////
	/// \brief Standard constructor
	/// \param width    width in pixels
	/// \param height   height in pixels
	/// \param title    title of window
	////////////////////////////////////////
	Engine(std::string title = "WindowTitle", uint32_t width = 1280, uint32_t height = 720);

	~Engine();

    ////////////////////////////////////////
    /// \bruef Start function for engine
    ////////////////////////////////////////
	void Run();

    bool IsOk() const;

private:
  //void HandleInput(sf::Time delta);
    void Update(sf::Time delta);

    void Render();
    void ProceedEvents();

	bool PrepareResources();

    void ChangeView();

    void ResetLevel();

    void LoadNextLevel();

    void Exit();

private:
    // FOR RESOURCES PREPARE
    bool no_error_;
    const sf::Vector2f default_size_ = sf::Vector2f(1280, 720);
    const float sprite_offset_ = 64.f;

    // SFML Members
    sf::RenderWindow window_;
    sf::Time time_per_frame_;
    sf::Time last_frame_time_;
    sf::Clock clock_;
    sf::View ui_view_;
	sf::View main_view_;
	sf::Music main_music_;

    // View vars
    float view_zoom_;
    float zoom_factor_;
    bool focus_on_player_;

    // Game vars
    uint32_t level_id_;

    ResourceManager manager_;
	GameMap game_map_;
    GameState state_;

    //User Interface
    PlayerUI player_ui_;
    MainMenu main_menu_;

	
};

#endif // ENGINE_HPP_
