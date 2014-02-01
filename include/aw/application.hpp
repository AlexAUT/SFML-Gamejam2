#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <SFML/Graphics/RenderWindow.hpp>

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
	};
}

#endif