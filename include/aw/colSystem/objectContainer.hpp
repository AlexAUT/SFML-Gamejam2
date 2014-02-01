#ifndef AWCOLOBJECTCONTAINER_HPP
#define AWCOLOBJECTCONTAINER_HPP

#include <vector>
#include <list>
#include <memory>

#include <SFML/System/Vector2.hpp>

#include "collisionLine.hpp"
#include "dynamicObject.hpp"

namespace sf
{
	class RenderTarget;
}

namespace aw
{
	namespace col
	{
		typedef std::unique_ptr<CollisionLine> ColLinePtr;
		typedef std::unique_ptr<DynamicObject> DynObjectPtr;

		typedef std::vector<ColLinePtr> ColLinesVec;
		typedef std::list<DynObjectPtr> DynObjectsVec;

		class ObjectContainer
		{
		public:
			
			void addCollisionLine(const sf::Vector2f &point1, const sf::Vector2f &point2);
			void removeCollisionLine(std::size_t index);

			void addDynamicObject(const sf::Vector2f &position, const sf::Vector2f &size);
			void removeDynamicDeadObjects();

			ColLinesVec &getCollisionLines();
			DynObjectsVec &getDynamicObjects();

			//This function may be slow, only for debugging reasons!
			void drawCollisionLines(sf::RenderTarget &window);

		private:

		private:
			ColLinesVec mCollisionLines;
			DynObjectsVec mDynamicObjects;
		};
	}
}

#endif