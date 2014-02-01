#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/System/Vector2.hpp>

#include "../../aw/colSystem/dynamicObject.hpp"

namespace aw
{
	class Player
	{
	public:
		Player();
		Player(col::DynamicObject *player);

		void setPlayer(col::DynamicObject *player);

		void update(const sf::Time &frameTime);

		sf::Vector2f getPosition() const;

	private:

	private:
		col::DynamicObject *mBody;

		float mRunSpeed;
		float mJumpStrength;
	};
}

#endif