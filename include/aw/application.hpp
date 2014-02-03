#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

#include "general\settings.hpp"
#include "states\stateMachine.hpp"


namespace aw
{
	class Application
	{
	public:
		Application();

		int run();

	private:

		void initWindow();

	private:
		sf::RenderWindow mWindow;

		Settings mSettings;
		StateMachine mStateMachine;

		//Temp
		sf::Font mFont;
		sf::Text mFpsDisplay;
		//
	};
}

#endif