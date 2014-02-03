#include "introMessage.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

#include <iostream>

namespace aw
{
	IntroMessage::IntroMessage()
	{
		mFont.loadFromFile("data/fonts/xirod.ttf");
		mInstruction.setFont(mFont);
		mInstruction.setCharacterSize(25);
	}

	void IntroMessage::setMessage(std::vector<std::string> &messages, const std::string &instruction)
	{
		mMessages.clear();
		sf::Vector2f position(0.f, 50.f);
		for (auto &it : messages)
		{
			mMessages.push_back(sf::Text(it, mFont, 18));
			position.x = 400 - (mMessages.back().getGlobalBounds().width / 2.f);
			position.y += 40.f;
			mMessages.back().setPosition(position);
		}

		mInstruction.setString(instruction);
		position.x = 400 - (mInstruction.getGlobalBounds().width / 2.f);
		position.y = 500;
		mInstruction.setPosition(position);
	}

	void IntroMessage::render(sf::RenderTarget &target)
	{
		for (auto &it : mMessages)
			target.draw(it);

		target.draw(mInstruction);
	}
}