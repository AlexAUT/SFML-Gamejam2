#include "menuState.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "gameState.hpp"
#include "../../aw/states/stateMachine.hpp"

namespace aw
{
	MenuState::MenuState(StateMachine &machine, sf::RenderWindow &window, Settings &settings):
		State(machine),
		mWindow(window),
		mSettings(settings),
		mGui(mWindow)
	{
		mGui.setGlobalFont("data/fonts/xirod.ttf");
		mGui.loadWidgetsFromFile("gui.txt");
		//tgui::Panel::Ptr panel(mGui);
		//panel->setSize(800, 600);
		//panel->hide();
		//panel->setBackgroundColor(sf::Color(0, 0, 0, 0));
		//panel->loadWidgetsFromFile("play.txt");

		//mGui.saveWidgetsToFile("gui.txt");
	}

	void MenuState::processEvent(const sf::Event &event)
	{
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			popStateNextFrame();

		mGui.handleEvent(event);
		//Gui event loop
		tgui::Callback callback;
		while (mGui.pollCallback(callback))
		{
			switch (callback.id)
			{
			case 1: mGui.get<tgui::Panel>("mainLayer")->hide(); mGui.get<tgui::Panel>("playLayer")->show(); break; //Play
			case 2: break; //Options
			case 3: break; //Credits
			case 4: break; //Help
			case 5: popStateNextFrame(); break; //Close
			case 10: mGui.get<tgui::Panel>("mainLayer")->show(); mGui.get<tgui::Panel>("playLayer")->hide(); break; //Back
			default: break;
			}

			if (callback.id > 100 && callback.id < 200)
			{
				std::string path = "data/levels/Level" + std::to_string(callback.id - 100) + ".txt";
				pushState(StateMachine::State_ptr(new GameState(getStateMachine(), mWindow, mSettings, path)));
			}
		}
	}

	void MenuState::update(const sf::Time &frameTime)
	{

	}

	void MenuState::render(sf::RenderTarget &target)
	{
		mGui.draw(true);
	}
}