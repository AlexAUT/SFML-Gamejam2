#include "system.hpp"


namespace aw
{
	namespace col
	{
		System::System()
		{
			//The physic need only to know where the dynamic objects are stored
			mPhysicSystem.setDynamicObjectsPtr(mObjectContainer.getDynamicObjects());
			//So the collisionHandler knows where the objects (collisionLines and dynamic objects) are stored
			mCollisionHandler.setPointers(mObjectContainer.getCollisionLines(), mObjectContainer.getDynamicObjects());
		}

		void System::update(const sf::Time &deltaTime)
		{
			//Update positions
			for (auto &it : *mObjectContainer.getDynamicObjects())
			{
				it.updatePosition(deltaTime);
			}
			//Check for collision after to prevent ugly jumping
			mPhysicSystem.update(deltaTime);
			mCollisionHandler.checkForCollision();
			
		}

		ObjectContainer &System::getObjectContainer()
		{
			return mObjectContainer;
		}

		const ObjectContainer &System::getObjectContainer() const
		{
			return mObjectContainer;
		}
	}
}