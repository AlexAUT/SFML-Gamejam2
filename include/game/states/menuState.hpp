#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP

#include "../../aw/states/state.hpp"

#include <TGUI/TGUI.hpp>

namespace sf
{
	class RenderWindow;
}

namespace aw
{
	class Settings;

	class MenuState : public State
	{
	public:
		MenuState(StateMachine &machine, sf::RenderWindow &window, Settings &settings);

		void processEvent(const sf::Event &evemt);
		void update(const sf::Time &frameTime);
		void render(sf::RenderTarget &target);

	private:

	private:
		sf::RenderWindow &mWindow;
		Settings &mSettings;

		tgui::Gui mGui;
	};
}

#endif
