#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <SFML/Graphics/View.hpp>

namespace aw
{
	class Camera
	{
	public:
		void setDefaultView(sf::View view);

		void update(sf::Vector2f position);

		sf::View getDefaultView() const;
		sf::View getGameView() const;

	private:

	private:
		sf::View mDefaultView;
		sf::View mGameView;

	};
}

#endif