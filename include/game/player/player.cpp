#include "player.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace aw
{
	Player::Player() :
		Player(nullptr)
	{}

	Player::Player(col::DynamicObject *player):
		mColObject(player),
		mRunSpeed(250.f),
		mJumpStrength(300.f)
	{
		mBody.setFillColor(sf::Color::Red);
		if (mColObject)
		{
			mBody.setPosition(mColObject->getPosition());
			mBody.setRadius(mColObject->getSize().x / 2.f);
		}
	}

	void Player::setPlayer(col::DynamicObject *player)
	{
		mColObject = player;
		if (mColObject)
		{
			mBody.setPosition(mColObject->getPosition());
			mBody.setRadius(mColObject->getSize().x / 2.f);
		}
	}

	void Player::update(const sf::Time &frameTime)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			mColObject->changeVelocity({ -mRunSpeed * frameTime.asSeconds(), 0.f });
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			mColObject->changeVelocity({ mRunSpeed * frameTime.asSeconds(), 0.f });

		if (mColObject->getState() == col::DynamicState::ON_GROUND)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				mColObject->setVelocity({ mColObject->getVelocity().x, -mJumpStrength });
				mColObject->changeState(col::DynamicState::FALLING);
				mColObject->setBoundLine(nullptr);
				mColObject->setCollisionImmune();
			}
		}

		
	}

	void Player::render(sf::RenderTarget &target)
	{
		mBody.setPosition(mColObject->getPosition());
		target.draw(mBody);
	}

	void Player::setPosition(sf::Vector2f position)
	{
		mColObject->setPosition(position);
		mBody.setPosition(mColObject->getPosition());
	}

	sf::Vector2f Player::getPosition() const
	{
		return mColObject->getPosition();
	}

	void Player::setVelocity(sf::Vector2f velocity)
	{
		mColObject->setVelocity(velocity);
		mBody.setPosition(mColObject->getPosition());
	}

	sf::Vector2f Player::getVelocity() const
	{
		return mColObject->getVelocity();
	}
}