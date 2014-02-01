#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <fstream>

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Utf.hpp>
#include <SFML/Window/ContextSettings.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Time.hpp>

namespace aw
{
	//Class declaration
	class Settings
	{
	public:
		struct WindowSettings
		{
			sf::Vector2u size = sf::Vector2u(800, 450);
			std::string title = "";
			sf::Uint32 style = sf::Style::Default;
			sf::ContextSettings settings;
			bool vsync = true;
			bool shaders = true;
			sf::Color clearColor = sf::Color::Black;
		} windowSettings; //no mW... prefix because the variable is public

		struct SoundSettings
		{
			bool enabled = true;
			float volumeMusic = 25;
			float volumeVFX = 25;
		} soundSettings; //no mW... prefix because the variable is public

		struct ApplicationSettings
		{
			sf::Time logicTick = sf::seconds(1.f/60.f);
		} applicationSettings;

	public:

		bool load();

		void save();


	private:
		bool loadWindowSettings();
		bool loadSoundSettings();

		void saveWindowSettings(std::fstream &file);
		void saveSoundSettings(std::fstream &file);

	private:

	};
}

#endif