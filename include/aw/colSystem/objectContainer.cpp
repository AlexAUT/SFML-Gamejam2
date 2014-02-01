#include "objectContainer.hpp"

#include <assert.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/CircleShape.hpp>

namespace aw
{
	namespace col
	{
		void ObjectContainer::addCollisionLine(const sf::Vector2f &point1, const sf::Vector2f &point2)
		{
			mCollisionLines.push_back(CollisionLine(point1, point2));
		}

		void ObjectContainer::removeCollisionLine(std::size_t index)
		{
			assert(index < mCollisionLines.size());

			mCollisionLines.erase(mCollisionLines.begin() + index);
		}

		void ObjectContainer::addDynamicObject(const sf::Vector2f &position, const sf::Vector2f &size)
		{
			mDynamicObjects.push_back(DynamicObject(position, size));
		}

		void ObjectContainer::removeDynamicObject(std::size_t index)
		{
			assert(index < mDynamicObjects.size());

			mDynamicObjects.erase(mDynamicObjects.begin() + index);
		}

		std::vector<CollisionLine> *ObjectContainer::getCollisionLines()
		{
			return &mCollisionLines;
		}

		std::vector<DynamicObject> *ObjectContainer::getDynamicObjects()
		{
			return &mDynamicObjects;
		}


		void ObjectContainer::drawCollisionLines(sf::RenderWindow &window)
		{
			sf::VertexArray toDraw(sf::Lines, mCollisionLines.size()*2);

			for (std::size_t i = 0; i < mCollisionLines.size()*2; i += 2)
			{
				toDraw[i].position = mCollisionLines[i / 2].getPoint(0);
				toDraw[i].color = sf::Color(164, 164, 0);

				toDraw[i+1].position = mCollisionLines[i / 2].getPoint(1);
				toDraw[i+1].color = sf::Color(164, 164, 0);
			}

			window.draw(toDraw);

			//Draw dynamic objects
			sf::CircleShape toDrawCircle;
			toDrawCircle.setFillColor(sf::Color::Red);

			for (auto &it : mDynamicObjects)
			{
				toDrawCircle.setPosition(it.getPosition());
				toDrawCircle.setRadius(it.getSize().x/2.f);
				window.draw(toDrawCircle);
			}
		}
	}
}