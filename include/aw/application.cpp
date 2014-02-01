#include "application.hpp"

#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

namespace aw
{
	Application::Application()
	{
		//Load settings (window/sound)
		mSettings.load();
		//init Window after loading the settings 
		initWindow();
		//Init start state
		
	}

	int Application::run()
	{
		//Frametime timer
		sf::Clock frameTimer;
		sf::Time frameTime;
		//Gameloop
		while (mWindow.isOpen())
		{
			//Calculate frameTime
			frameTime += frameTimer.restart();
			//Event handling
			sf::Event event;
			while (mWindow.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					mWindow.close();

				mStateMachine.processEvent(event);
			}
			//Update game logic
			//Compare the frametime with the logicTick rate
			while (frameTime > mSettings.applicationSettings.logicTick)
			{
				//Decrase the frameTimer per tick
				frameTime -= mSettings.applicationSettings.logicTick;
				//Update the gamelogic with logicTick
				mStateMachine.update(mSettings.applicationSettings.logicTick);
			}
			//Rendering
			mWindow.clear(mSettings.windowSettings.clearColor);
			mStateMachine.render(mWindow);
			mWindow.display();
		}
		
		return 0;
	}

	void Application::initWindow()
	{
		//Create the window with the loaded settings in mSettings
		sf::VideoMode mode(mSettings.windowSettings.size.x, mSettings.windowSettings.size.y);
		mWindow.create(mode, mSettings.windowSettings.title, mSettings.windowSettings.style, mSettings.windowSettings.settings);
		//Set vsync
		mWindow.setVerticalSyncEnabled(mSettings.windowSettings.vsync);
	}
}