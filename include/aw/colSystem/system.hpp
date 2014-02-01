#ifndef AWCOLSYSTEM_HPP
#define AWCOLSYSTEM_HPP

#include "objectContainer.hpp"
#include "physicSystem.hpp"
#include "collisionHandler.hpp"

namespace sf
{
	class Time;
}

namespace aw
{
	namespace col
	{
		class System
		{
		public:
			System();

			void update(const sf::Time &deltaTime);

			ObjectContainer &getObjectContainer();
			const ObjectContainer &getObjectContainer() const;

		private:

		private:
			ObjectContainer mObjectContainer;
			PhysicSystem mPhysicSystem;
			CollisionHandler mCollisionHandler;
		};
	}
}

#endif