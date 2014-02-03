#ifndef MAP_HPP
#define MAP_HPP

#include <string>
#include <fstream>
#include <vector>

#include <SFML/Graphics/RectangleShape.hpp>

namespace sf
{
	class RenderTarget;
	class Time;
}

namespace aw
{
	class Player;

	class Map
	{
	public:
		bool load(const std::string &path);
		
		void movePlayerWithCollision(Player &player, const sf::Time &frameTime);
		bool playerReachedFinish(sf::Vector2f position);

		void render(sf::RenderTarget &target);

	private:
		void loadStaticObjects(std::fstream &file);
		void loadDeathZoneObjects(std::fstream &file);

	private:
		std::vector<sf::RectangleShape> mStaticObjects;
		std::vector<sf::RectangleShape> mDeathZones;

		float mFinishLine;
	};
}

#endif