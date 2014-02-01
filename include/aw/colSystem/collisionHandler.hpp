#ifndef AWCOLCOLLISIONHANDLER_HPP
#define AWCOLCOLLISIONHANDLER_HPP

#include "objectContainer.hpp"

namespace aw
{
	namespace col
	{
		class CollisionHandler
		{
		public:

			void setPointers(ColLinesVec *colLinesPtr, DynObjectsVec *dynObjectsPtr);

			void checkForCollision();

		private:

			bool checkWhenBound(DynamicObject &obj);
			void checkForCollision(DynamicObject &obj);

		private:
			ColLinesVec *mCollisionLinesPtr;
			DynObjectsVec *mDynamixObjectsPtr;
		};
	}
}

#endif