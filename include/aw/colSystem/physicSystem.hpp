#ifndef AWCOLPHYSICSYSTEM_HPP
#define AWCOLPHYSICSYSTEM_HPP

#include "objectContainer.hpp"

namespace sf
{
	class Time;
}

namespace aw
{
	namespace col
	{
		class PhysicSystem
		{
		public:
			PhysicSystem();

			void setDynamicObjectsPtr(DynObjectsVec *ptr);

			void update(const sf::Time &deltaTime);

		private:

		private:
			DynObjectsVec *mDynamicObjects;

			float mGravitation;
		};
	}
}

#endif