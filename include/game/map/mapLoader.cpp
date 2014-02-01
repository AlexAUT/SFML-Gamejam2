#include "mapLoader.hpp"

#include <sstream>
#include <fstream>

namespace aw
{
	void loadStaticLines(std::fstream &file, col::ObjectContainer &container);

	bool loadMap(const std::string &path, col::ObjectContainer &container)
	{
		std::fstream file(path.c_str(), std::ios::in);
		if (!file.is_open())
			return false;

		std::string line;
		while (std::getline(file, line))
		{
			if (line == "[static]")
				loadStaticLines(file, container);
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
}