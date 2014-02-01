#ifndef AWCOLDYNAMICOBJECT_HPP
#define AWCOLDYNAMICOBJECT_HPP

#include <SFML/System/Vector2.hpp>

namespace sf
{
	class Time;
}

namespace aw
{
	namespace col
	{
		class CollisionLine;

		enum class DynamicState
		{
			FALLING,
			ON_GROUND
		};

		class DynamicObject
		{
		public:
			DynamicObject();
			DynamicObject(const sf::Vector2f &position, const sf::Vector2f &size);

			void updatePosition(const sf::Time &deltaTime);

			void setPosition(const sf::Vector2f &position);
			void setLastPosition(const sf::Vector2f &position);
			void setSize(const sf::Vector2f &size);
			void setVelocity(const sf::Vector2f &velocity);
			void changeVelocity(const sf::Vector2f &value);
			void setBoundLine(CollisionLine *ptr);
			void setCollisionImmune();
			void setAlive(bool val);

			const sf::Vector2f &getPosition() const;
			const sf::Vector2f &getLastPosition() const;
			const sf::Vector2f &getSize() const;
			const sf::Vector2f &getVelocity() const;
			const CollisionLine *getBoundLine() const;
			DynamicState getState() const;
			bool getImmune();
			bool isAlive() const;

			void changeState(DynamicState newState);
		private:

		private:
			DynamicState mState;

			sf::Vector2f mPosition;
			sf::Vector2f mLastPosition;
			sf::Vector2f mSize;

			sf::Vector2f mVelocity;

			CollisionLine *mBoundLine;

			bool mCollisionImmune;
			bool mAlive;
		};
	}
}

#endif