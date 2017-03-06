#include "Engine.hpp"

Engine::Engine(std::string title, uint32_t width, uint32_t height)
    :game_map_(manager_)
    ,view_zoom_(2.f)
    ,zoom_factor_(0.1f)
    ,focus_on_player_(0)
    ,no_error_ (1)
    ,level_id_(1)
    ,state_(GameState::MENU)
{
    if (!PrepareResources())
        no_error_ = false;
    else
    {
        window_.create(sf::VideoMode(width, height), title);
        window_.setFramerateLimit(60);
        time_per_frame_ = sf::seconds(1.f / 60.f);

        main_menu_.AddButton(*manager_.GetTexture(TEXTURE_ID::BTN_BG), *manager_.GetTexture(TEXTURE_ID::BTN_ACTIVE), manager_.GetFont(), "PLAY", ButtonType::MENU_PLAY,sf::Vector2f((window_.getSize().x/2.f)-100.f,100.f));
        main_menu_.AddButton(*manager_.GetTexture(TEXTURE_ID::BTN_BG), *manager_.GetTexture(TEXTURE_ID::BTN_ACTIVE), manager_.GetFont(), "ABOUT", ButtonType::MENU_ABOUT,sf::Vector2f((window_.getSize().x / 2.f) - 100.f, 200.f));
        main_menu_.AddButton(*manager_.GetTexture(TEXTURE_ID::BTN_BG), *manager_.GetTexture(TEXTURE_ID::BTN_ACTIVE), manager_.GetFont(), "EXIT", ButtonType::MENU_EXIT, sf::Vector2f((window_.getSize().x / 2.f) - 100.f, 300.f));

        //Show MainMenu


	    //!Game map load and initialize assets
	    game_map_.LoadMap(1);
        game_map_.PrintToConsole();

        // For setting up player and artifacts
	    //game_map_.Initialize(); Moved to LoadMap function of GameMap object

        

	    //! Prepare view 
        sf::Vector2f view_center_pos = sf::Vector2f((game_map_.GetMapWidth()/2) * sprite_offset_, (game_map_.GetMapHeight()/2) * sprite_offset_);

	    main_view_.setSize(default_size_); // default = 1280 x 720
        main_view_.setCenter(view_center_pos);
        main_view_.zoom(2.f);
        main_view_.setViewport(sf::FloatRect(0, 0, 1, 1));


        player_ui_.SetFont(manager_.GetFont());
        player_ui_.SetBackground(*manager_.GetTexture(TEXTURE_ID::UI_BACKGROUND));

        ui_view_.setViewport(sf::FloatRect(0,0,1,1));

    }

}

Engine::~Engine()
{
}

void Engine::Run()
{
	while (window_.isOpen())
	{

        player_ui_.SetMovesCounter(game_map_.GetPlayerMoves());
        window_.setTitle("Sokoban || Moves: " + UtilityFunctions::IntToString(game_map_.GetPlayerMoves()));

        Render();

        if (game_map_.CheckArtifacts())
            LoadNextLevel();

        ProceedEvents();

		last_frame_time_ += clock_.restart();
        while (last_frame_time_ > time_per_frame_)
        {
            last_frame_time_ -= time_per_frame_;
            Update(time_per_frame_);
        }
	}
}

bool Engine::IsOk() const
{
    return no_error_;
}

/*
    void Engine::HandleInput(sf::Time delta)
    {
        //(REAL-TIME MOVING...) useless now
	    float offset = sprite_offset_ *delta.asSeconds();

	    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		    player_.move(sf::Vector2f(-1.f * offset,0.f));
	    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		    player_.move(sf::Vector2f(1.f * offset, 0.f));
	    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		    player_.move(sf::Vector2f(0.f, -1.f * offset));
	    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		    player_.move(sf::Vector2f(0.f, 1.f * offset));

    }
*/

void Engine::Update(sf::Time delta)
{
	//HandleInput(delta); (REAL-TIME MOVING...) It's useless in this game :)
    // SFML don't provide method for KeyDown, KeyUp in sf::Keyboard :<

    if (focus_on_player_)
        main_view_.setCenter(game_map_.GetPlayerPosition().x - (sprite_offset_ / 2), game_map_.GetPlayerPosition().y - (sprite_offset_ / 2));

}

void Engine::Render()
{
    window_.clear(sf::Color(0x1f, 0x1f, 0x1f, 0));

    if (state_ == GameState::PLAY)
    {
        // GAME
        window_.setView(main_view_);
        window_.draw(game_map_);

        window_.setView(ui_view_);
        window_.draw(player_ui_);
        //END GAME
    }
    else
    {
        window_.draw(main_menu_);
    }
    
    window_.display();

}

void Engine::ProceedEvents()
{
    sf::Event events;
    while (window_.pollEvent(events))
    {
		if (events.type == sf::Event::Closed)
		{
            Exit();
		}
        if (state_ == GameState::MENU)
        {
            if (events.type == sf::Event::MouseButtonPressed)
            {
                main_menu_.CheckPosition(sf::Mouse::getPosition(window_));
            }
            if (events.type == sf::Event::MouseButtonReleased)
            {
                if (ButtonType::MENU_PLAY == main_menu_.CheckClick(sf::Mouse::getPosition(window_)))
                    state_ = GameState::PLAY;
                else if (ButtonType::MENU_ABOUT == main_menu_.CheckClick(sf::Mouse::getPosition(window_)))
                    MessageBox(0, "Remake of classic Sokoban game\nSome practice! :D\nMade by: Krzysztof Begiedza", "About", MB_OK | MB_ICONINFORMATION);
                else if (ButtonType::MENU_EXIT == main_menu_.CheckClick(sf::Mouse::getPosition(window_)))
                    Exit();

            }
            
        }
        else
        {

		    if (events.type == sf::Event::KeyPressed)
		    {
                if (events.key.code == sf::Keyboard::F1)
                    ResetLevel(); 
                if (events.key.code == sf::Keyboard::F2)
                    LoadNextLevel();
                if (events.key.code == sf::Keyboard::V)
                    ChangeView();
			    if (events.key.code == sf::Keyboard::A || events.key.code == sf::Keyboard::Left)
				    game_map_.MovePlayer(sf::Vector2f(-1.f * sprite_offset_, 0.f));
			    if (events.key.code == sf::Keyboard::D || events.key.code == sf::Keyboard::Right)
                    game_map_.MovePlayer(sf::Vector2f(1.f * sprite_offset_, 0.f));
			    if (events.key.code == sf::Keyboard::W || events.key.code == sf::Keyboard::Up)
                    game_map_.MovePlayer(sf::Vector2f(0.f, -1.f * sprite_offset_));
			    if (events.key.code == sf::Keyboard::S || events.key.code == sf::Keyboard::Down)
                    game_map_.MovePlayer(sf::Vector2f(0.f, 1.f * sprite_offset_));
                if (events.key.code == sf::Keyboard::Add && view_zoom_ > 1.f)
                {
                    main_view_.zoom(1 - zoom_factor_);
                    view_zoom_ -= zoom_factor_;
                }
                if (events.key.code == sf::Keyboard::Subtract && view_zoom_ < 2.f)
                {
                    main_view_.zoom(1 + zoom_factor_);
                    view_zoom_ += zoom_factor_;
                }

            }
		}
		
    }
}

bool Engine::PrepareResources()
{ 
	if (!manager_.LoadTexture(TEXTURE_ID::FLOOR, "data/img/floor.png"))
		return false;
    if (!manager_.LoadTexture(TEXTURE_ID::FLOOR_TRIGGER, "data/img/floor_trigger.png"))
        return false;
	if (!manager_.LoadTexture(TEXTURE_ID::WALL, "data/img/wall.png"))
		return false;
    if (!manager_.LoadTexture(TEXTURE_ID::PLAYER, "data/img/player.png"))
        return false;
	if (!manager_.LoadTexture(TEXTURE_ID::OBJECT, "data/img/object_rust.png"))
		return false;
    if (!manager_.LoadTexture(TEXTURE_ID::OBJECT_GLOW, "data/img/object_glow.png"))
        return false;
    if (!manager_.LoadTexture(TEXTURE_ID::UI_BACKGROUND, "data/img/ui_bg.png"))
        return false;
    if (!manager_.LoadTexture(TEXTURE_ID::BTN_BG, "data/img/btn.png"))
        return false;
    if (!manager_.LoadTexture(TEXTURE_ID::BTN_ACTIVE, "data/img/btn_pressed.png"))
        return false;
    if (!manager_.LoadFont("data/fonts/Quikhand.ttf")) // (!manager_.LoadFont("data/fonts/BLKCHCRY.ttf"))
        return false;

	return true;
}

void Engine::ChangeView()
{
    if(focus_on_player_)
    {
        focus_on_player_ = 0;
        main_view_.setCenter(sf::Vector2f((game_map_.GetMapWidth() / 2) * sprite_offset_, (game_map_.GetMapHeight() / 2) * sprite_offset_));

    }
    else
    {
        focus_on_player_ = 1;
        main_view_.setCenter(game_map_.GetPlayerPosition().x - (sprite_offset_/2), game_map_.GetPlayerPosition().y - (sprite_offset_ / 2));
    }
}

void Engine::ResetLevel()
{
    game_map_.LoadMap(level_id_);
    


    //! DEBUG:
    std::cout << "LVL: " << level_id_ << std::endl;
    game_map_.PrintToConsole();
}

void Engine::LoadNextLevel()
{
    
    if (MessageBox(0, "Czy wczytaæ kolejn¹ mapê?", "Next level?", MB_YESNO | MB_ICONQUESTION) == IDYES)
    {
        if (!game_map_.LoadMap(level_id_+1))
        {
            if (MessageBox(0, "Map loading fault", "ERROR", MB_ICONERROR | MB_OK) == IDOK)
                Exit();
            return;
        }
        level_id_++;
    }
    else
        Exit();

    //! DEBUG:
    std::cout << "LVL: " << level_id_ << std::endl;
    game_map_.PrintToConsole();
    std::cout << std::endl;
}

void Engine::Exit()
{
   if(MessageBox(0, "Czy chcesz wyjœæ?", "wyjœcie?", MB_YESNO | MB_ICONQUESTION) != IDYES)
        return;
   window_.close();
        
}