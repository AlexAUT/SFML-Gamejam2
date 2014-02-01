#include "player.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/Window/Keyboard.hpp>

namespace aw
{
	Player::Player() :
		Player(nullptr)
	{}

	Player::Player(col::DynamicObject *player):
		mBody(player),
		mRunSpeed(250.f),
		mJumpStrength(300.f)
	{}

	void Player::setPlayer(col::DynamicObject *player)
	{
		mBody = player;
	}

	void Player::update(const sf::Time &frameTime)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			mBody->changeVelocity({ -mRunSpeed * frameTime.asSeconds(), 0.f });
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			mBody->changeVelocity({ mRunSpeed * frameTime.asSeconds(), 0.f });

		if (mBody->getState() == col::DynamicState::ON_GROUND)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				mBody->setVelocity({ mBody->getVelocity().x, -mJumpStrength });
				mBody->changeState(col::DynamicState::FALLING);
				mBody->setBoundLine(nullptr);
				mBody->setCollisionImmune();
			}
		}
	}

	void Player::setPosition(sf::Vector2f position)
	{
		mBody->setPosition(position);
	}

	sf::Vector2f Player::getPosition() const
	{
		return mBody->getPosition();
	}

	void Player::setVelocity(sf::Vector2f velocity)
	{
		mBody->setVelocity(velocity);
	}

	sf::Vector2f Player::getVelocity() const
	{
		return mBody->getVelocity();
	}
}