#include "enemySpawner.hpp"

#include "../../aw/colSystem/objectContainer.hpp"

#include <iostream>

namespace aw
{
	EnemySpawner::EnemySpawner(col::ObjectContainer &container) :
		mColObjectContainer(container)
	{

	}

	void EnemySpawner::setSpawnBehaviour(sf::Time spawnRate, sf::Vector2f position, sf::Vector2f size, sf::Time lifeTime, sf::Color color)
	{
		mBehaviour.spawnRate = spawnRate;
		mBehaviour.position = position;
		mBehaviour.size = size;
		mBehaviour.lifeTime = lifeTime;
		mBehaviour.color = color;
	}

	void EnemySpawner::addEnemy(sf::Vector2f position, sf::Vector2f size, sf::Time lifeTime, sf::Color color)
	{
		mColObjectContainer.addDynamicObject(position, size);
		mEnemies.emplace_back(&*mColObjectContainer.getDynamicObjects().back(), lifeTime, color);
	}

	void EnemySpawner::update(const sf::Time &frameTime)
	{
		mTimeSinceLastSpawn += frameTime;
		if (mTimeSinceLastSpawn > mBehaviour.spawnRate)
		{
			mTimeSinceLastSpawn -= mBehaviour.spawnRate;
			addEnemy(mBehaviour.position, mBehaviour.size, mBehaviour.lifeTime, mBehaviour.color);
		}

		for (auto &it : mEnemies)
			it.update(frameTime);

		auto size = mEnemies.size();
		mEnemies.remove_if([](Enemy &e) { return !e.isAlive(); });
		if (size != mEnemies.size())
			mColObjectContainer.removeDynamicDeadObjects();
	}

	void EnemySpawner::render(sf::RenderTarget &target)
	{
		for (auto &it : mEnemies)
			it.render(target);
	}
}