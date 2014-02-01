#include "collisionHandler.hpp"

#include <iostream>

bool isIntersecting(const sf::Vector2f &p1, const sf::Vector2f &p2, const sf::Vector2f &p3, const sf::Vector2f &p4, sf::Vector2f &collisionPoint);

namespace aw
{
	namespace col
	{
		void CollisionHandler::setPointers(ColLinesVec *colLinesPtr, DynObjectsVec *dynObjectsPtr)
		{
			mCollisionLinesPtr = colLinesPtr;
			mDynamixObjectsPtr = dynObjectsPtr;
		}

		void CollisionHandler::checkForCollision()
		{
			//Check every dynamic object with every static object (if not bound)
			for (auto &it : *mDynamixObjectsPtr)
			{
				if (it.getImmune())
					continue;
				//Check if its bound to a line already
				if (it.getBoundLine())
				{
					//Do some stuff
					if (!checkWhenBound(it))
					{
						//The dynamicObject got off the line, 
						//No it has no bound line -> check for collision
						it.setLastPosition(sf::Vector2f(it.getLastPosition().x, it.getLastPosition().y - 5.f));
						checkForCollision(it);
					}
				}
				else
				{
					//Check for collision
					checkForCollision(it);
				}
			}
		}

		bool CollisionHandler::checkWhenBound(DynamicObject &obj)
		{
			//TODO: improve it, atm its only a hack...
			//Huge number to simulate a real line... and not a line segment
			sf::Vector2f point1 = sf::Vector2f(obj.getPosition().x + (obj.getSize().x / 2.f), -100000000);
			sf::Vector2f point2 = sf::Vector2f(obj.getPosition().x + (obj.getSize().x / 2.f),  100000000);

			sf::Vector2f collisionPoint;

			if (isIntersecting(point1, point2, obj.getBoundLine()->getPoint(0), obj.getBoundLine()->getPoint(1), collisionPoint))
			{
				//Set position to the collisionPoint
				sf::Vector2f newPos = sf::Vector2f(collisionPoint.x - (obj.getSize().x / 2.f), collisionPoint.y - obj.getSize().y);
				obj.setPosition(newPos);

				return true;
			}
			else
			{
				//Set the y velocity to a right value
				obj.setVelocity(sf::Vector2f(obj.getVelocity().x, obj.getVelocity().x * -obj.getBoundLine()->getSlope()));
				obj.setBoundLine(nullptr);
				
				return false;
			}
		}

		void CollisionHandler::checkForCollision(DynamicObject &obj)
		{
			//Calculate the middle south point of the obj
			sf::Vector2f southLastFrame = sf::Vector2f(obj.getLastPosition().x + (obj.getSize().x / 2.f), obj.getLastPosition().y + obj.getSize().y);
			sf::Vector2f southCurrent = sf::Vector2f(obj.getPosition().x + (obj.getSize().x / 2.f), obj.getPosition().y + obj.getSize().y);

			
			//Test the southPoints with every line for intersection
			for (auto &it : *mCollisionLinesPtr)
			{
				sf::Vector2f collisionPoint;
				if (isIntersecting(southCurrent, southLastFrame, it.getPoint(0), it.getPoint(1), collisionPoint))
				{
					//Inform the dynamic objects its now bound to a line (this in only for performance reason needed)
					obj.setBoundLine(&it);
					//Set position to the collisionPoint
					sf::Vector2f newPos = sf::Vector2f(collisionPoint.x - (obj.getSize().x / 2.f), collisionPoint.y - obj.getSize().y);
					obj.setPosition(newPos);
					//Increase/Decrease the X speed, to simulate a impact
					float addToXVelocity = obj.getVelocity().y * -0.5f * it.getSlope();
					obj.changeVelocity(sf::Vector2f(addToXVelocity, 0));
					//Set the y-Velocity to 0, stop falling through the line
					obj.setVelocity(sf::Vector2f(obj.getVelocity().x, 0));
					//Do some work to simulate he is on that line
					//checkWhenBound(obj);
					//Do not check for other collisions
					break;
				}
			}
		}
	}
}

//Global func, this handles the line intersection
bool isIntersecting(const sf::Vector2f &p1, const sf::Vector2f &p2, const sf::Vector2f &p3, const sf::Vector2f &p4, sf::Vector2f &collisionPoint)
{
	// Store the values for fast access and easy
	// equations-to-code conversion
	float x1 = p1.x, x2 = p2.x, x3 = p3.x, x4 = p4.x;
	float y1 = p1.y, y2 = p2.y, y3 = p3.y, y4 = p4.y;

	float d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	// If d is zero, there is no intersection
	if (d == 0) return false;

	// Get the x and y
	float pre = (x1*y2 - y1*x2), post = (x3*y4 - y3*x4);
	float x = (pre * (x3 - x4) - (x1 - x2) * post) / d;
	float y = (pre * (y3 - y4) - (y1 - y2) * post) / d;
	
	float epsilon = 0.1f;
	// Check if the x and y coordinates are within both lines
	if (x < (std::min(x1, x2) - epsilon) || x >(std::max(x1, x2) + epsilon) ||
		x < (std::min(x3, x4) - epsilon) || x >(std::max(x3, x4) + epsilon))
		return false;
	if (y < (std::min(y1, y2) - epsilon) ||
		y >(std::max(y1, y2) + epsilon) ||
		y < (std::min(y3, y4) - epsilon) ||
		y >(std::max(y3, y4) + epsilon))
		return false;

	// Return the point of intersection
	collisionPoint.x = x;
	collisionPoint.y = y;
	return true;
}