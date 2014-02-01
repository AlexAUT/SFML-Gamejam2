#include "collisionLine.hpp"

#include <assert.h>
#include <iostream>

namespace aw
{
	namespace col
	{
		CollisionLine::CollisionLine() :
			CollisionLine(sf::Vector2f(), sf::Vector2f())
		{

		}

		CollisionLine::CollisionLine(const sf::Vector2f &point1, const sf::Vector2f &point2) :
			mPoints{ { point1, point2 } }
		{
			//Calculate slope
			sf::Vector2f *left, *right; //The order is important, dont rely on the user

			if (mPoints[0].x < mPoints[1].x)
			{
				left = &mPoints[0];
				right = &mPoints[1];
			}
			else
			{
				left = &mPoints[1];
				right = &mPoints[0];
			}

			sf::Vector2f lineVector = *right - *left;
			//std::cout << "Linevector: " << lineVector.x << " | " << lineVector.y << std::endl;
			//- to reverse the Y axis
			mSlope = -(lineVector.y / lineVector.x);
			//std::cout << mSlope << std::endl;
		}

		const sf::Vector2f &CollisionLine::getPoint(std::size_t index) const
		{
			assert(index < 2);

			return mPoints[index];
		}

		float CollisionLine::getSlope() const
		{
			return mSlope;
		}
	}
}