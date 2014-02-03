#include "player.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <iostream>

static const float PERIMETER = 157.08f;

namespace aw
{
	Player::Player() :
		Player({ 0.f, 0.f }, { 0.f, 0.f })
	{}

	Player::Player(sf::Vector2f position, sf::Vector2f size) :
		mRotationSpeed(0.f),
		mRunSpeed(475.f),
		mJumpStrength(150.f),
		mIsOnGround(false)
	{
		mBody.setFillColor(sf::Color::Red);
		mBody.setPosition(position);
		mBody.setSize(size);
		mVelocity = { 0.f, 0.f };

		mTexture.loadFromFile("data/sprites/player.png");
		mTexture2.loadFromFile("data/sprites/player2.png");
		mSprite.setTexture(mTexture);
	}

	void Player::update(const sf::Time &frameTime)
	{
		mVelocity.y += 800.f * frameTime.asSeconds();
		if (mVelocity.x < mRunSpeed)
			mVelocity.x += 190.f * frameTime.asSeconds();
		mTimeInAir += frameTime;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && (mIsOnGround || mTimeInAir < sf::seconds(0.25f)))
		{
			mVelocity.y = -300.f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			mBody.setSize({ mBody.getSize().x, 25.f });
			mSprite.setTextureRect(sf::IntRect(0, 0, 50, 25));
		}
		else
		{
			if (mIsOnGround && mBody.getSize().y < 30.f)
			{
				setPosition({ mBody.getPosition().x, mBody.getPosition().y - 25.f });
			}
			mBody.setSize({ mBody.getSize().x, 50.f });
			mSprite.setTextureRect(sf::IntRect(0, 0, 50, 50));
		}

		//Update rotation spped
		updateRotation(frameTime);
	}

	void Player::updateRotation(const sf::Time &frameTime)
	{
		//Calculate rotation speed
		if (mBody.getSize().y > 48.f)
		{
			if (mIsOnGround)
			{
				mRotationSpeed = 360.f * ((mVelocity.x * frameTime.asSeconds()) / PERIMETER);
			}
			else
			{
				if (mRotationSpeed > 0)
					mRotationSpeed -= 25.f * frameTime.asSeconds();
				else if (mRotationSpeed < 0)
					mRotationSpeed = 0.f;
			}
		}
		else
		{
			mRotationSpeed = 0.f;
			mSprite.setRotation(0);
		}

		if (std::abs(mRotationSpeed) < 5.f)
		{
			mSprite.setTexture(mTexture);
		}
		else
		{
			mSprite.setTexture(mTexture2);
		}
	}

	void Player::render(sf::RenderTarget &target)
	{
		//target.draw(mBody);
		mSprite.setOrigin(25.f, 25.f);
		mSprite.rotate(mRotationSpeed);
		target.draw(mSprite);
	}

	void Player::setPosition(sf::Vector2f position)
	{
		mBody.setPosition(position);
		mSprite.setPosition(position + sf::Vector2f(25.f, 25.f));
	}

	sf::Vector2f Player::getPosition() const
	{
		return mBody.getPosition();
	}

	void Player::setVelocity(sf::Vector2f velocity)
	{
		mVelocity = velocity;
	}

	sf::Vector2f Player::getVelocity() const
	{
		return mVelocity;
	}

	sf::Vector2f Player::getSize() const
	{
		return mBody.getSize();
	}

	bool Player::isOnGround() const
	{
		return mIsOnGround;
	}

	void Player::setOnGround(bool val)
	{
		if (val && !mIsOnGround)
			mTimeInAir = sf::Time::Zero;

		mIsOnGround = val;
	}

	void Player::setAlive(bool val)
	{
		mAlive = val;
	}

	bool Player::isAlive() const
	{
		return mAlive;
	}

	void Player::resetRotation()
	{
		mRotationSpeed = 0;
		mSprite.setRotation(0.f);
	}
}