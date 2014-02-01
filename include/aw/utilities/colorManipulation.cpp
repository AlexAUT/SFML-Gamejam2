#include "colorManipulation.hpp"

#include <SFML/Graphics/Color.hpp>

namespace aw
{
	namespace color
	{
		void invert(sf::Color &color)
		{
			color.r = 255 - color.r;
			color.g = 255 - color.g;
			color.b = 255 - color.b;
		}
	}
}