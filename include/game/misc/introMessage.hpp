#ifndef INTROMESSAGE_HPP
#define INTORMESSAGE_HPP

#include <vector>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace aw
{
	class IntroMessage
	{
	public:
		IntroMessage();

		void setMessage(std::vector<std::string> &message, const std::string &instruction);

		void render(sf::RenderTarget &target);

	private:
		sf::Font mFont;
		std::vector<sf::Text> mMessages;
		sf::Text mInstruction;
	};
}

#endif