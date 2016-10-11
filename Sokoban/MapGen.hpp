#ifndef MAPGEN_HPP_
#define MAPGEN_HPP_

#include <SFML/Graphics.hpp>
#include <random>

#include "ResourceType.h"

#include "UtilityFunctions.hpp"

class MapGenerator
{
public:
    static void Generate(int mapTab[16][32], sf::Vector2f & player_spawn);
};


#endif // MAPGEN_HPP_