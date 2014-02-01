#include "objectContainer.hpp"

#include <assert.h>
#include <iostream>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/CircleShape.hpp>

namespace aw
{
	namespace col
	{
		void ObjectContainer::addCollisionLine(const sf::Vector2f &point1, const sf::Vector2f &point2)
		{
			mCollisionLines.push_back(ColLinePtr(new CollisionLine(point1, point2)));
		}

		void ObjectContainer::removeCollisionLine(std::size_t index)
		{
			assert(index < mCollisionLines.size());

			mCollisionLines.erase(mCollisionLines.begin() + index);
		}

		void ObjectContainer::addDynamicObject(const sf::Vector2f &position, const sf::Vector2f &size)
		{
			mDynamicObjects.push_back(DynObjectPtr(new DynamicObject(position, size)));
		}

		void ObjectContainer::removeDynamicDeadObjects()
		{
			std::cout << mDynamicObjects.size() << "  |  ";
			mDynamicObjects.remove_if([](DynObjectPtr &p){return !p->isAlive(); });
			std::cout << mDynamicObjects.size() << "  |  " << std::endl;
		}

		ColLinesVec &ObjectContainer::getCollisionLines()
		{
			return mCollisionLines;
		}

		DynObjectsVec &ObjectContainer::getDynamicObjects()
		{
			return mDynamicObjects;
		}


		void ObjectContainer::drawCollisionLines(sf::RenderTarget &window)
		{
			sf::VertexArray toDraw(sf::Lines, mCollisionLines.size()*2);

			for (std::size_t i = 0; i < mCollisionLines.size()*2; i += 2)
			{
				toDraw[i].position = mCollisionLines[i / 2]->getPoint(0);
				toDraw[i].color = sf::Color(164, 164, 0);

				toDraw[i+1].position = mCollisionLines[i / 2]->getPoint(1);
				toDraw[i+1].color = sf::Color(164, 164, 0);
			}
			window.draw(toDraw);
		}
	}
}