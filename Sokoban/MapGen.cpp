#include "MapGen.hpp"

// HACK DEBUG ONLY:
#include <Windows.h>
#include <iostream>


void MapGenerator::Generate(int mapTab[16][32], sf::Vector2f & player_spawn)
{

#pragma region RoomTemplate
    int rooms[12][3][3] = {
        {
            1,  1,  3,
            1,  3,  3,
            1,  1,  1
        },
        {
            1,  1,  1,
            1,  1,  1,
            1,  1,  1
        },
        {
            3,  1,  1,
            1,  1,  1,
            1,  1,  1
        },
        {
            3,  1,  1,
            1,  1,  1,
            1,  1,  3
        },
        {
            3,  3,  1,
            1,  1,  1,
            1,  1,  1
        },
        {
            3,  3,  3,
            3,  1,  1,
            3,  1,  1
        },
        {
            3,  1,  1,
            1,  1,  1,
            3,  1,  1
        },
        {
            3,  1,  1,
            1,  1,  1,
            3,  1,  3
        },
        {
            3,  3,  3,
            1,  3,  1,
            1,  1,  1
        },
        {
            3,  1,  3,
            3,  1,  1, 
            3,  3,  3
        },
        {
            3,  3,  3,
            3,  3,  3,
            3,  3,  3
        },
        {
            3,  3,  3,
            3,  3,  3,
            1,  1,  1
        },
    };
#pragma endregion

    // map variables
    int                     artifacts_;
    sf::Vector2i            player_spawn_;

    std::random_device      rd;

    artifacts_ = (rd()% 5)+2;



    for (int i = 0; i < 16; ++i)
    {
        for (int j = 0; j < 32; ++j)
        {
            mapTab[i][j] = (int)TEXTURE_ID::FLOOR;
        }
    }



    int level;
    for (int i = 1; i < 14; i+=3)
    {
        for (int j = 1; j < 31;j+=3)
        {
            level = rd() % 12;
            for (int k = 0; k < 3; ++k)
            {
                for (int l = 0; l < 3; ++l)
                {
                    mapTab[i + k][j + l] = rooms[level][k][l];
                }
            }
        }
    }

    // HACK: Delete magic numbers
    for (int y = 0; y < 16; ++y)
    {

        mapTab[y][0] = (int)TEXTURE_ID::WALL;
        mapTab[y][31] = (int)TEXTURE_ID::WALL;
    }
    for (int x = 0; x < 32; ++x)
    {
        mapTab[0][x] = (int)TEXTURE_ID::WALL;
        mapTab[15][x] = (int)TEXTURE_ID::WALL;
    }

    // HACK: closed rooms checking

    // HACK: artifacts generator




    //////////////////////////////
    ///WALL DELETION
    //////////////////////////////

#pragma region WallDeletion
    for (int i = 0; i < 16; ++i)
    {
        int counter = 0;
        bool isSurrounded = true;
        int j = -1;
        while(isSurrounded && j < 31)
        {
            counter = 0;
            ++j;
            if (mapTab[i][j] == 3)
            {
                //std::cout << "i: " << i << " j: " << j << "\n";
                if (i > 0 && j > 0)
                {
                    if (mapTab[i - 1][j - 1] != (int)TEXTURE_ID::WALL && mapTab[i - 1][j - 1] != (int)TEXTURE_ID::NONE)
                        counter++;
                }
                if (i < 15 && j < 31)
                {
                    if (mapTab[i + 1][j + 1] != (int)TEXTURE_ID::WALL && mapTab[i + 1][j + 1] != (int)TEXTURE_ID::NONE)
                        counter++;
                }

                
                if (j > 0)
                {
                    if (mapTab[i][j - 1] != (int)TEXTURE_ID::WALL && mapTab[i][j - 1] != (int)TEXTURE_ID::NONE)
                        counter++;
                    if (i < 15)
                    {
                        if (mapTab[i+1][j - 1] != (int)TEXTURE_ID::WALL && mapTab[i+1][j - 1] != (int)TEXTURE_ID::NONE)
                            counter++;
                    }
                    
                }
                if (i > 0)
                {
                    if (mapTab[i-1][j] != (int)TEXTURE_ID::WALL && mapTab[i-1][j] != (int)TEXTURE_ID::NONE)
                        counter++;
                    if (j < 31)
                    {
                        if (mapTab[i - 1][j+1] != (int)TEXTURE_ID::WALL && mapTab[i - 1][j+1] != (int)TEXTURE_ID::NONE)
                            counter++;
                    }
                }
                if (i < 15)
                {
                    if (mapTab[i+1][j] != (int)TEXTURE_ID::WALL && mapTab[i + 1][j] != (int)TEXTURE_ID::NONE)
                        counter++;
                }
                if (j < 31)
                {
                    if (mapTab[i][j+1] != (int)TEXTURE_ID::WALL && mapTab[i][j+1] != (int)TEXTURE_ID::NONE)
                        counter++;
                }
                if (counter == 0)
                    mapTab[i][j] = (int)TEXTURE_ID::NONE;
            }
            
        }

    }
#pragma endregion 

    while (mapTab[player_spawn_.y][player_spawn_.x] != (int)TEXTURE_ID::FLOOR)
    {
        player_spawn_ = sf::Vector2i((rd() % 30)+1, (rd() % 14)+1);
        player_spawn = sf::Vector2f(player_spawn_.x * 64.f, player_spawn_.y * 64.f);
    }
    
    // adding player spawn floor
    mapTab[player_spawn_.y][player_spawn_.x] = (int)TEXTURE_ID::FLOOR;

}
