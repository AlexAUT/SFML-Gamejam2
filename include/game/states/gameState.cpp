#include "gameState.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "../../aw/general/settings.hpp"

#include "../map/mapLoader.hpp"

namespace aw
{
	GameState::GameState(StateMachine &stateMachine, sf::RenderWindow &window, Settings &settings) :
		State(stateMachine),
		mWindow(window),
		mSettings(settings),
		mGoingBack(false)
	{
		//Load the map
		loadMap("data/levels/test.txt", mCollisionSystem.getObjectContainer(), mEnemySpawner);
		//Add player to the collision system
		mCollisionSystem.getObjectContainer().addDynamicObject({ 25.f, 0.f }, { 35.f, 35.f });
		mPlayer.setPlayer(&*mCollisionSystem.getObjectContainer().getDynamicObjects().front());
		//Setup the default view for the camera
		mCamera.setDefaultView(mWindow.getDefaultView());
	}

	void GameState::processEvent(const sf::Event &event)
	{
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			popStateNextFrame();
	}

	void GameState::update(const sf::Time &frameTime)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
		{
			if (!mGoingBack)
			{
				mTracker.startGoingBackInTime(mPlayer.getPosition(), mPlayer.getVelocity());
				mGoingBack = true;
			}
			auto newPosVel = mTracker.goingBack(frameTime);
			mPlayer.setPosition(newPosVel[0]);
			mPlayer.setVelocity(newPosVel[1]);
		}
		else
		{
			mGoingBack = false;
		}

		if (!mGoingBack)
		{
			//Controls
			mPlayer.update(frameTime);
			mTracker.update(frameTime, mPlayer.getPosition(), mPlayer.getVelocity());
			//Update Enviroment
			mCollisionSystem.update(frameTime);
			//Update enemies
			for (auto &it : mEnemySpawner)
				it.update(frameTime);
		}

		//Update camera
		mCamera.update(mPlayer.getPosition());
	}

	void GameState::render(sf::RenderTarget &target)
	{
		target.setView(mCamera.getGameView());
		mCollisionSystem.getObjectContainer().drawCollisionLines(target);
		//Render Enemies
		for (auto &it : mEnemySpawner)
			it.render(target);
		mPlayer.render(target);
		target.setView(mCamera.getDefaultView());
	}
}