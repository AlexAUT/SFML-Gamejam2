#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>


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
		Player(sf::Vector2f position, sf::Vector2f size);


		void update(const sf::Time &frameTime);
		void updateRotation(const sf::Time &frameTime);
		void render(sf::RenderTarget &target);

		void setPosition(sf::Vector2f position);
		sf::Vector2f getPosition() const;

		void setVelocity(sf::Vector2f velocity);
		sf::Vector2f getVelocity() const;

		sf::Vector2f getSize() const;

		bool isOnGround() const;
		void setOnGround(bool val);

		void setAlive(bool val);
		bool isAlive() const;

		void resetRotation();

	private:

	private:
		bool mAlive;

		sf::RectangleShape mBody;
		sf::Texture mTexture;
		sf::Texture mTexture2;
		sf::Sprite mSprite;
		float mRotationSpeed;

		sf::Vector2f mVelocity;

		float mRunSpeed;
		float mJumpStrength;

		bool mIsOnGround;
		sf::Time mTimeInAir;
	};
}

#endif