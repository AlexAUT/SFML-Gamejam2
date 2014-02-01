#include "enemy.hpp"

#include "../../aw/colSystem/dynamicObject.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

namespace aw
{
	Enemy::Enemy(col::DynamicObject *body, sf::Time lifeTime, sf::Color color) :
		mColObject(body),
		mLifeTime(lifeTime),
		mTimeAlive(sf::Time::Zero)
	{
		mBody.setPosition(mColObject->getPosition());
		mBody.setRadius(mColObject->getSize().x / 2.f);
		mBody.setFillColor(color);
	}

	void Enemy::update(const sf::Time &frameTime)
	{
		mTimeAlive += frameTime;

		if (mTimeAlive > mLifeTime)
		{
			mColObject->setAlive(false);
		}

		mBody.setPosition(mColObject->getPosition());
	}

	void Enemy::render(sf::RenderTarget &target)
	{
		target.draw(mBody);
	}

	bool Enemy::isAlive() const
	{
		return mColObject->isAlive();
	}
}