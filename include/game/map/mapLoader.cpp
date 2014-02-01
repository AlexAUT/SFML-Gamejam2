#include "mapLoader.hpp"

#include <sstream>
#include <fstream>
#include <iostream>


namespace aw
{
	void loadStaticLines(std::fstream &file, col::ObjectContainer &container);
	void loadSpawner(std::fstream &file, col::ObjectContainer &container, std::vector<EnemySpawner> &spawner);

	bool loadMap(const std::string &path, col::ObjectContainer &container, std::vector<EnemySpawner> &enemySpawners)
	{
		std::fstream file(path.c_str(), std::ios::in);
		if (!file.is_open())
			return false;

		std::string line;
		while (std::getline(file, line))
		{
			if (line == "[static]")
				loadStaticLines(file, container);
			else if (line == "[spawner]")
				loadSpawner(file, container, enemySpawners);
		}

		return true;
	}

	void loadStaticLines(std::fstream &file, col::ObjectContainer &container)
	{
		std::string line;
		while (std::getline(file, line) && line != "[/static]")
		{
			std::stringstream sstr(line);
			sf::Vector2f start, end;
			sstr >> start.x >> start.y >> end.x >> end.y;
			container.addCollisionLine(start, end);
		}
	}

	void loadSpawner(std::fstream &file, col::ObjectContainer &container, std::vector<EnemySpawner> &spawner)
	{
		std::string line;
		while (std::getline(file, line) && line != "[/spawner]")
		{
			std::stringstream sstr(line);
			sf::Vector2f position, size;
			float rate, lifeTime, r, g, b;

			sstr >> position.x >> position.y >> size.x >> rate >> lifeTime >> r >> g >> b;
			size.y = size.x;
			sf::Color color(static_cast<sf::Uint8>(r), static_cast<sf::Uint8>(b), static_cast<sf::Uint8>(g));

			spawner.push_back(EnemySpawner(container));
			spawner.back().setSpawnBehaviour(sf::seconds(rate), position, size, sf::seconds(lifeTime), color);
			std::cout << spawner.size();
		}
	}
}