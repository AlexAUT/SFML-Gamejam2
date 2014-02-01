#ifndef MAPLOADER_HPP
#define MAPLOADER_HPP

#include <string>
#include <vector>

#include "../../aw/colSystem/objectContainer.hpp"
#include "../spawner/enemySpawner.hpp"

namespace aw
{
	bool loadMap(const std::string &path, col::ObjectContainer &container, std::vector<EnemySpawner> &enemySpawners);
}

#endif