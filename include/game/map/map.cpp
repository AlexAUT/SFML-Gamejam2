#include "map.hpp"

#include <sstream>
#include <fstream>
#include <iostream>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>

#include "../player/player.hpp"

namespace aw
{
	bool Map::load(const std::string &path)
	{
		mFinishLine = 1000000.f;
		std::fstream file(path.c_str(), std::ios::in);

		if (!file.is_open())
			return false;

		std::string line;
		while (std::getline(file, line))
		{
			if (line == "[static]")
				loadStaticObjects(file);
			if (line == "[deathZones]")
				loadDeathZoneObjects(file);
			if (line == "[finish]")
			{
				std::getline(file, line);
				mFinishLine = std::stof(line);
			}
		}

		return true;
	}

	void Map::movePlayerWithCollision(Player &player, const sf::Time &frameTime)
	{
		//Update playerposition
		player.setPosition(player.getPosition() + (player.getVelocity() * frameTime.asSeconds()));
		player.setAlive(true);
		//Set player to be not on ground (collision detection will set it to true of he is on the ground
		player.setOnGround(false);
		for (auto &it : mStaticObjects)
		{
			//Check if there is a rect under 
			//Get player floatRect
			sf::FloatRect playerRect(player.getPosition(), player.getSize());
			//Area = the intersection
			sf::FloatRect area;
			if (it.getGlobalBounds().intersects(playerRect, area))
			{
				if (area.width > area.height)
				{
					if (area.contains({ area.left, player.getPosition().y }))
					{
						//Head against the wall
						player.setPosition({ player.getPosition().x, player.getPosition().y + area.height });
						if (player.getVelocity().y < 0)
							player.setVelocity({ player.getVelocity().x, 0.f });
					}
					else
					{
						//Standing on the ground
						player.setOnGround(true);
						player.setPosition({ player.getPosition().x, player.getPosition().y - area.height });
						if (player.getVelocity().y > 0)
							player.setVelocity({ player.getVelocity().x, 0.f });
					}
				}
				else if (area.width < area.height)
				{
					if (area.contains({ player.getPosition().x + player.getSize().x - 1.f, area.top + 1.f }))
					{
						//Right side crash
						player.setPosition({ player.getPosition().x - area.width, player.getPosition().y });
						if (player.getVelocity().x > 0)
							player.setVelocity({ 0.f, player.getVelocity().y});
					}
					else
					{
						//Left side crash
						player.setPosition({ player.getPosition().x + area.width, player.getPosition().y });
						if (player.getVelocity().x < 0)
							player.setVelocity({ 0.f, player.getVelocity().y });
					}
				}
			}
		}
		//Check if the player is in a deathzone
		sf::FloatRect playerRect(player.getPosition(), player.getSize());
		for (auto &it : mDeathZones)
		{
			if (it.getGlobalBounds().intersects(playerRect))
			{
				player.setAlive(false);
			}
		}
	}

	bool Map::playerReachedFinish(sf::Vector2f position)
	{
		if (position.x > mFinishLine)
			return true;

		return false;
	}

	void Map::render(sf::RenderTarget &target)
	{
		for (auto &it : mStaticObjects)
			target.draw(it);
		for (auto &it : mDeathZones)
			target.draw(it);

		//Draw finish line
		sf::RectangleShape finish;
		finish.setPosition({ mFinishLine, target.getView().getCenter().y - target.getView().getCenter().y });
		finish.setSize({ 7.f, target.getView().getSize().y * 2.f });
		finish.setFillColor(sf::Color::Green);
		target.draw(finish);
	}


	void Map::loadStaticObjects(std::fstream &file)
	{
		mStaticObjects.clear();
		std::string line;
		while (std::getline(file, line) && line != "[/static]")
		{
			sf::Vector2f pos, size;
			int r, g, b;

			std::stringstream sstr(line);
			sstr >> pos.x >> pos.y >> size.x >> size.y >> r >> g >> b;

			mStaticObjects.emplace_back(size);
			mStaticObjects.back().setPosition(pos);
			mStaticObjects.back().setFillColor(sf::Color(r, g, b));
		}
	}

	void Map::loadDeathZoneObjects(std::fstream &file)
	{
		mDeathZones.clear();
		std::string line;
		while (std::getline(file, line) && line != "[/deathZones]")
		{
			sf::Vector2f pos, size;

			std::stringstream sstr(line);
			sstr >> pos.x >> pos.y >> size.x >> size.y;

			mDeathZones.emplace_back(size);
			mDeathZones.back().setPosition(pos);
			mDeathZones.back().setFillColor(sf::Color(255, 255, 0));
		}
	}
}