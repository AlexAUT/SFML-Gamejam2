#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <vector>

#include <SFML/Audio/Music.hpp>

#include "../../aw/states/state.hpp"

#include "../player/positionTracker.hpp"
#include "../camera/camera.hpp"
#include "../misc/introMessage.hpp"
#include "../player/player.hpp"

#include "../map/map.hpp"

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
		GameState(StateMachine &statemachine, sf::RenderWindow &winow, Settings &settings, const std::string &path);

		void processEvent(const sf::Event &event);
		void update(const sf::Time &frameTime);
		void render(sf::RenderTarget &target);

	private:

		void loadLevel();

	private:
		sf::RenderWindow &mWindow;
		Settings &mSettings;

		std::string mPath;

		enum class GameStatus
		{
			INTRO,
			RUNNING,
			PAUSED,
			CRASHED,
			FINISHED
		}mGameStatus;

		PositionTracker mTracker;
		bool mGoingBack;

		Camera mCamera;

		Player mPlayer;
		Map mMap;

		IntroMessage mIntroMessage;

		sf::Music mMusic;
	};
}
#endif