#ifndef ENEMYSPAWNER_HPP
#define ENEMYSPAWNER_HPP

#include <list>

#include "enemy.hpp"

namespace aw
{
	namespace col
	{
		class ObjectContainer;
	}

	class EnemySpawner
	{
	public:
		EnemySpawner(col::ObjectContainer &container);

		void setSpawnBehaviour(sf::Time spawnRate, sf::Vector2f position, sf::Vector2f size, sf::Time lifeTime, sf::Color color = sf::Color::Blue);

		void update(const sf::Time &frameTime);
		void render(sf::RenderTarget &target);

	private:

		void addEnemy(sf::Vector2f position, sf::Vector2f size, sf::Time lifeTime, sf::Color color = sf::Color::Blue);

	private:
		col::ObjectContainer &mColObjectContainer;

		struct SpawnBehaviour
		{
			sf::Time spawnRate;
			sf::Vector2f position;
			sf::Vector2f size;
			sf::Time lifeTime;
			sf::Color color;
		}mBehaviour;
		
		sf::Time mTimeSinceLastSpawn;

		std::list<Enemy> mEnemies;
	};
}

#endif