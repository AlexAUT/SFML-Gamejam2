#ifndef MAPLOADER_HPP
#define MAPLOADER_HPP

#include <string>

#include "../../aw/colSystem/objectContainer.hpp"

namespace aw
{
	bool loadMap(const std::string &path, col::ObjectContainer &container);
}

#endif