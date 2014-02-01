#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include "../../aw/colSystem/dynamicObject.hpp"

namespace sf
{
	class RenderTarget;
}

namespace aw
{
	class Player
	{
	public:
		Player();
		Player(col::DynamicObject *player);

		void setPlayer(col::DynamicObject *player);

		void update(const sf::Time &frameTime);
		void render(sf::RenderTarget &target);

		void setPosition(sf::Vector2f position);
		sf::Vector2f getPosition() const;

		void setVelocity(sf::Vector2f velocity);
		sf::Vector2f getVelocity() const;

	private:

	private:
		col::DynamicObject *mColObject;
		sf::CircleShape mBody;

		float mRunSpeed;
		float mJumpStrength;
	};
}

#endif