#include "GameMap.hpp"

GameMap::GameMap(ResourceManager & r)
    :trigger_count_(0)
{
	ptr_manager_ = &r;
	spawn_position_ = sf::Vector2f(0.f, 0.f);
}

GameMap::~GameMap()
{
	ptr_manager_ = nullptr;
	delete ptr_manager_;
}

bool GameMap::LoadMap(unsigned int level)
{

    trigger_count_ = 0;
    
    char temp;

	//Clear
    artifacts_.clear();
	WipeMap();
    ResetPlayer();


    std::fstream file;
	std::string file_path = "data/maps/map"+UtilityFunctions::IntToString(level)+".skb";
	
    file.open(file_path);
    if (!file.is_open())
        return false;

    
	int x = 0, y = 0;

	char *buffer = new char[33];

	int level_width = 0;
	int level_height = 0;

	int max_width = level_width;

    while (file.peek() != EOF)
    {
		file.getline(buffer, 33);

		for (size_t i = 0; i < std::strlen(buffer); i++)
		{
			switch (buffer[i])
			{
			case '.':
				ground_id_map_[y][i] = (int)MAP_ELEMENT::FLOOR;
				break;
			case '#':
				ground_id_map_[y][i] = (int)MAP_ELEMENT::WALL;
				break;
			case 'p':
				spawn_position_ = sf::Vector2f(64.f*i, 64.f*y);
				ground_id_map_[y][i] = (int)MAP_ELEMENT::FLOOR;
				break;
			case 'X':
				++trigger_count_;
				ground_id_map_[y][i] = (int)MAP_ELEMENT::FLOOR_TRIGGER;
				break;
			case 'o':
				artifacts_.push_back(Artifact(64.f*i, 64.f*y, ptr_manager_));
				ground_id_map_[y][i] = (int)MAP_ELEMENT::FLOOR;
				break;
			default:
				ground_id_map_[y][i] = (int)MAP_ELEMENT::NONE;
				level_width--;
				break;	
			}

			level_width++;
			
		}
		max_width = std::max(level_width, max_width);
		level_width = 0;

        x = 0;

        y++;

		level_height++;
		memset(buffer, 0, sizeof(buffer));
    }

	delete[] buffer;
    
    file.close();

	current_level_size_ = sf::Vector2f(max_width, level_height);

    InitializePlayer();

    return true;
}

void GameMap::PrintToConsole()
{
	for (int i = 0; i < map_size_y_; ++i)
	{
		for (int j = 0; j < map_size_x_; ++j)
			std::cout << ground_id_map_[i][j] << " ";
		std::cout << std::endl;
	}
}

void GameMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	sf::Sprite spr;
	for (int y = 0; y < map_size_y_; ++y)
	{
		for (int x = 0; x < map_size_x_; ++x)
		{
			if ((TEXTURE_ID)ground_id_map_[y][x] != TEXTURE_ID::NONE)
			{
				spr = ptr_manager_->GetSprite((TEXTURE_ID)ground_id_map_[y][x]);
				spr.setPosition(sf::Vector2f(x * 64.f, y * 64.f));
				target.draw(spr, states);
			}
		}
	}
    target.draw(player_,states);
    
    for (std::vector<Artifact>::const_iterator iter = artifacts_.begin(); iter != artifacts_.end(); ++iter)
        target.draw(*iter, states);
}

int GameMap::GetMapElementId(sf::Vector2f pos) const
{
	// 64x64 px  <--- sprite size
    int x = (int)pos.x / 64; 
    int y = (int)pos.y / 64;
    return ground_id_map_[y][x];
}

sf::Vector2f GameMap::GetSpawnPosition() const
{
	return spawn_position_;
}

const int & GameMap::GetMapWidth() const
{
    return map_size_x_;
}

const int & GameMap::GetMapHeight() const
{
    return map_size_y_;
}

bool GameMap::CheckCollision(sf::Vector2f pos, sf::Vector2f oryginal_pos, sf::Vector2f offset)
{
    int s_x = (int)pos.x / 64;
    int s_y = (int)pos.y / 64;

    int oryginal_x = (int)oryginal_pos.x/64;
    int oryginal_y = (int)oryginal_pos.y/64;

    if (ground_id_map_[oryginal_y][oryginal_x] != 1 && ground_id_map_[oryginal_y][oryginal_x] != 2)
        return true;
    if (ground_id_map_[s_y][s_x] == 1 || ground_id_map_[s_y][s_x] == 2)
    {
        for (std::vector<Artifact>::iterator it = artifacts_.begin(); it != artifacts_.end(); ++it)
        {
            if (it->getPosition() == pos)
            {
                if (!CheckCollision(sf::Vector2f(it->getPosition() + offset), it->getPosition(), offset))
                {
                    it->setPosition(it->getPosition() + offset);
                    return false;
                }
                else 
                    return true;
            }
        }
        return false;
    }
    else
        return true;

}

void GameMap::MovePlayer(sf::Vector2f offset)
{
    if (!CheckCollision(player_.getPosition() + offset, player_.getPosition(),offset))
    {
        player_.move(offset);
        CheckArtifacts();
    }
}

sf::Vector2f GameMap::GetPlayerPosition() const
{
    return player_.getPosition();
}

void GameMap::InitializePlayer()
{
    player_.setTexture(*ptr_manager_->GetTexture(TEXTURE_ID::PLAYER));
    player_.setPosition(GetSpawnPosition());

}

bool GameMap::CheckArtifacts()
{
    matched_count_ = 0;

    for (std::vector<Artifact>::iterator it = artifacts_.begin(); it != artifacts_.end(); ++it)
    {
        if(GetMapElementId(it->getPosition()) == 2 )
        {
            it->SetTrigger(true);
			matched_count_++;
        }
        else
            it->SetTrigger(false);
        it->Update();
    }

    if (matched_count_ == trigger_count_)
        return true;
    else
        return false;
}

const uint32_t & GameMap::GetArtifactsCount()
{
	return trigger_count_;
}

const uint32_t & GameMap::GetMatchedArtifactsCount()
{
	return matched_count_;
}

UINT32 GameMap::GetPlayerMoves()
{
    return player_.GetMoveCounter();
}

const sf::Vector2f & GameMap::GetCurrentLevelSize()
{
	return current_level_size_;
}

void GameMap::ResetPlayer()
{
    player_.Reset();
}

void GameMap::WipeMap()
{
	for (size_t i = 0; i < 16; i++)
	{
		for (size_t j = 0; j < 32; j++)
		{
			ground_id_map_[i][j] = (int)TEXTURE_ID::NONE;
		}
	}
}

