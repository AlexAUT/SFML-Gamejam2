#include "camera.hpp"


namespace aw
{
	void Camera::setDefaultView(sf::View view)
	{
		mDefaultView = view;
		mGameView = mDefaultView;
	}

	void Camera::update(sf::Vector2f position)
	{
		mGameView.setCenter({ position.x + 250.f, position.y });
	}

	sf::View Camera::getDefaultView() const
	{
		return mDefaultView;
	}

	sf::View Camera::getGameView() const
	{
		return mGameView;
	}
}