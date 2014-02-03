#include "application.hpp"

#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include "../game/states/menuState.hpp"

namespace aw
{
	Application::Application()
	{
		//Load settings (window/sound)
		mSettings.load();
		//init Window after loading the settings 
		initWindow();
		//Init start state
		StateMachine::State_ptr game(new MenuState(mStateMachine, mWindow, mSettings));
		mStateMachine.pushState(game);

		//Temp
		mFont.loadFromFile("data/fonts/xirod.ttf");
		mFpsDisplay.setFont(mFont);
		mFpsDisplay.setColor(sf::Color::Red);
		mFpsDisplay.setCharacterSize(15);
		//
	}

	int Application::run()
	{
		//Frametime timer
		sf::Clock fpsTimer;
		sf::Clock frameTimer;
		sf::Time frameTime;
		//Gameloop
		while (mWindow.isOpen() && !mStateMachine.isEmpty())
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
			//Temp
			mFpsDisplay.setString(std::to_string(static_cast<int>(1.f / fpsTimer.restart().asSeconds())));
			//Rendering
			mWindow.clear(mSettings.windowSettings.clearColor);
			mStateMachine.render(mWindow);

			mWindow.draw(mFpsDisplay);
			mWindow.display();
		}
		
		mSettings.save();
		return 0;
	}

	void Application::initWindow()
	{
		//Create the window with the loaded settings in mSettings
		sf::VideoMode mode(mSettings.windowSettings.size.x, mSettings.windowSettings.size.y);
		mWindow.create(mode, mSettings.windowSettings.title, mSettings.windowSettings.style, mSettings.windowSettings.settings);
		//Set vsync
		mWindow.setVerticalSyncEnabled(mSettings.windowSettings.vsync);
		mWindow.setVerticalSyncEnabled(true);
	}
}