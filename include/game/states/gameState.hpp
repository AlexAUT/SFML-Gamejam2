#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "../../aw/states/state.hpp"
#include "../../aw/colSystem/system.hpp"

#include "../player/player.hpp"
#include "../camera/camera.hpp"

namespace sf
{
	class RenderWindow;
}

namespace aw
{
	class Settings;

	class GameState : public State
	{
	public:
		GameState(StateMachine &statemachine, sf::RenderWindow &winow, Settings &settings);

		void processEvent(const sf::Event &event);
		void update(const sf::Time &frameTime);
		void render(sf::RenderTarget &target);

	private:

	private:
		sf::RenderWindow &mWindow;
		Settings &mSettings;

		col::System mCollisionSystem;

		Player mPlayer;

		Camera mCamera;
	};
}
#endif