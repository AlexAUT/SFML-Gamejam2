#include "physicSystem.hpp"

#include <iostream>

#include <SFML/System/Time.hpp>


namespace aw
{
	namespace col
	{
		PhysicSystem::PhysicSystem() :
			mDynamicObjects(nullptr),
			mGravitation(700.f)
		{

		}

		void PhysicSystem::setDynamicObjectsPtr(DynObjectsVec *ptr)
		{
			mDynamicObjects = ptr;
		}

		void PhysicSystem::update(const sf::Time &deltaTime)
		{
			//Check if a vector is available
			if (mDynamicObjects)
			{
				//Add to every object the mGravitation
				for (auto &it : *mDynamicObjects)
				{
					if (it.getState() == DynamicState::ON_GROUND)
					{
						
						//Rolling depends on the slope of the line
						float accerlerationX = it.getBoundLine()->getSlope() * -0.5f * mGravitation;
						////std::cout << "Accerleration X: " << accerlerationX << std::endl;
						it.changeVelocity(sf::Vector2f(accerlerationX * deltaTime.asSeconds(), 0));
						//Now adjust the yVelocity to match
					}
					else if (it.getState() == DynamicState::FALLING)
					{
						it.changeVelocity(sf::Vector2f(0, mGravitation * deltaTime.asSeconds()));
					}
				}
			}
		}
	}
}