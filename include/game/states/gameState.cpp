#include "gameState.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "../../aw/general/settings.hpp"

namespace aw
{
	GameState::GameState(StateMachine &stateMachine, sf::RenderWindow &window, Settings &settings) :
		State(stateMachine),
		mWindow(window),
		mSettings(settings)
	{
		mCollisionSystem.getObjectContainer().addCollisionLine({ 0.f, 500.f }, { 500.f, 600.f });
		mCollisionSystem.getObjectContainer().addDynamicObject({ 25.f, 0.f }, { 35.f, 35.f });
		mPlayer.setPlayer(&mCollisionSystem.getObjectContainer().getDynamicObjects()->at(0));

		mCamera.setDefaultView(mWindow.getDefaultView());
	}

	void GameState::processEvent(const sf::Event &event)
	{
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			popStateNextFrame();
	}

	void GameState::update(const sf::Time &frameTime)
	{
		//Controls
		mPlayer.update(frameTime);
		//Update Enviroment
		mCollisionSystem.update(frameTime);
		//Update camera
		mCamera.update(mPlayer.getPosition());
	}

	void GameState::render(sf::RenderTarget &target)
	{
		target.setView(mCamera.getGameView());
		mCollisionSystem.getObjectContainer().drawCollisionLines(target);
		target.setView(mCamera.getDefaultView());
	}
}