#ifndef ENEMEY_HPP
#define ENEMEY_HPP

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/CircleShape.hpp>

namespace sf
{
	class RenderTarget;
}

namespace aw
{
	namespace col
	{
		class DynamicObject;
	}

	class Enemy
	{
	public:

		Enemy(col::DynamicObject *body, sf::Time lifeTime, sf::Color color);

		void update(const sf::Time &frameTime);

		void render(sf::RenderTarget &target);

		bool isAlive() const;

	private:

	private:

		col::DynamicObject *mColObject;
		sf::CircleShape mBody;

		sf::Time mLifeTime;
		sf::Time mTimeAlive;
	};
}

#endif