#ifndef AWCOLCOLLISIONLINE_HPP
#define AWCOLCOLLISIONLINE_HPP

#include <array>

#include <SFML/System/Vector2.hpp>

namespace aw
{
	namespace col
	{
		class CollisionLine
		{
		public:
			CollisionLine();
			CollisionLine(const sf::Vector2f &point1, const sf::Vector2f &point2);

			const sf::Vector2f &getPoint(std::size_t index) const;
			float getSlope() const;

		private:

		private:
			std::array<sf::Vector2f, 2> mPoints;

			float mSlope;

		};
	}
}

#endif