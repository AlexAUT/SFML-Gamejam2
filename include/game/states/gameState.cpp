#include "gameState.hpp"

#include <iostream>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "../../aw/general/settings.hpp"

#include "../map/mapLoader.hpp"

void loadMessages(const std::string &path, std::string tag, std::vector<std::string> &messages);

namespace aw
{
	GameState::GameState(StateMachine &stateMachine, sf::RenderWindow &window, Settings &settings, const std::string &path) :
		State(stateMachine),
		mWindow(window),
		mSettings(settings),
		mGameStatus(GameStatus::INTRO),
		mGoingBack(false),
		mPlayer({ 100.f, 0.f }, { 50.f, 50.f })
	{
		mPath = path;
		loadLevel();

		mMusic.openFromFile("data/music/music.ogg");
		mMusic.setVolume(25.f);
	}

	void GameState::processEvent(const sf::Event &event)
	{
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			popStateNextFrame();

		if (event.type == sf::Event::KeyReleased)
		{
			if (mGameStatus == GameStatus::INTRO && event.key.code == sf::Keyboard::Return)
			{
				mGameStatus = GameStatus::RUNNING;
			}
			else if (mGameStatus == GameStatus::FINISHED && event.key.code == sf::Keyboard::Return)
			{
				mGameStatus = GameStatus::INTRO;
				//Get next level path
				int lvlNumber = std::stoi(mPath.substr(17));
				lvlNumber++;
				mPath = "data/levels/Level" + std::to_string(lvlNumber) + ".txt";
				//Load next level
				loadLevel();
			}
		}
	}

	void GameState::update(const sf::Time &frameTime)
	{
		if (mGameStatus == GameStatus::RUNNING)
		{
			//Check if music is running
			if (mMusic.getStatus() != sf::Music::Playing)
				mMusic.play();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
			{
				if (!mGoingBack)
				{
					mGoingBack = true;
					mTracker.startGoingBackInTime(mPlayer.getPosition(), mPlayer.getVelocity());
				}
			}
			else
				mGoingBack = false;

			if (mGoingBack)
			{
				auto values = mTracker.goingBack(frameTime);
				mPlayer.setPosition(values[0]);
				mPlayer.setVelocity(values[1]);
				mPlayer.updateRotation(frameTime);
			}
			else
			{
				//Update velocity (Does not move the character!)
				mPlayer.update(frameTime);
				//Moves the character + checks and handle collision
				mMap.movePlayerWithCollision(mPlayer, frameTime);
				//Check if player is dead
				if (!mPlayer.isAlive())
				{
					mGameStatus = GameStatus::CRASHED;
					std::vector<std::string> temp = { "You died!", "Now you have 2 options", "Press B to go back in time", "Press R to restart" };
					mIntroMessage.setMessage(temp, "");
				}
				//Store player movements
				mTracker.update(frameTime, mPlayer.getPosition(), mPlayer.getVelocity());
				//Check if player reached finish
				if (mMap.playerReachedFinish(mPlayer.getPosition()))
				{
					mGameStatus = GameStatus::FINISHED;
					std::vector<std::string> msg;
					loadMessages(mPath, "finishMessage", msg);
					mIntroMessage.setMessage(msg, "");
				}
			}
		}
		else if (mGameStatus == GameStatus::CRASHED)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
			{
				mGameStatus = GameStatus::RUNNING;
				auto values = mTracker.goingBack(frameTime);
				mPlayer.setPosition(values[0]);
				mPlayer.setVelocity(values[1]);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
			{
				mGameStatus = GameStatus::INTRO;
				loadLevel();
			}
		}

		mCamera.update(mPlayer.getPosition());
	}

	void GameState::render(sf::RenderTarget &target)
	{
		target.setView(mCamera.getGameView());
		mMap.render(target);
		mPlayer.render(target);
		target.setView(mCamera.getDefaultView());

		if (mGameStatus != GameStatus::RUNNING)
		{
			sf::RectangleShape rect({ 800.f, 600.f });
			rect.setFillColor({ 0, 0, 0, 180 });
			target.draw(rect);
		}
		if (mGameStatus == GameStatus::INTRO || mGameStatus == GameStatus::FINISHED || mGameStatus == GameStatus::CRASHED)
		{
			mIntroMessage.render(target);
		}
	}

	void GameState::loadLevel()
	{
		mPlayer.resetRotation();
		mPlayer.setPosition({ 100.f, 50.f });
		mPlayer.setVelocity({ 0.f, 0.f });
		//Load the map
		mMap.load(mPath);
		std::vector<std::string> message;
		loadMessages(mPath, "message", message);
		//Init intro message
		mIntroMessage.setMessage(message, "Press enter to start the game!");
		//Setup the default view for the camera
		mCamera.setDefaultView(mWindow.getDefaultView());
	}
}

void loadMessages(const std::string &path, std::string tag, std::vector<std::string> &messages)
{
	std::fstream file(path.c_str(), std::ios::in);

	std::string line;
	while (std::getline(file, line))
	{
		if (line == "[" + tag + "]")
		{
			while (std::getline(file, line) && line != ("[/" + tag + "]"))
			{
				messages.push_back(line);
			}
			break;
		}
	}
}