#ifndef POSITIONTRACKER_HPP
#define POSITIONTRACKER_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>

#include <deque>
#include <array>

namespace aw
{
	class PositionTracker
	{
	public:

		void update(const sf::Time &frameTime, sf::Vector2f position, sf::Vector2f velocity);

		void startGoingBackInTime(sf::Vector2f position, sf::Vector2f velocity);
		std::array<sf::Vector2f, 2> goingBack(const sf::Time &frameTime);

	private:

	private:
		std::deque<std::array<sf::Vector2f, 2>> mPastPositions;

		sf::Time mSinceLastSave;
		sf::Time mBetweenSaves = sf::seconds(0.1f);

		float mPercentage = 0.f;
	};
}

#endif