#include "settings.hpp"

#include <sstream>
#include <iostream>

namespace aw
{
	/////////////////////////////////////////////////
	bool Settings::load()
	{
		if (!loadWindowSettings())
			return false;

		if (!loadSoundSettings())
			return false;

		return true;
	}
	/////////////////////////////////////////////////
	void  Settings::save()
	{
		//Open the file
		std::fstream file("data/options.cfg", std::ios::out | std::ios::trunc);
		//Read header
		file << "Kroniax options file. Creator Alexander Weinrauch\n-------------------------------------\n\n";
		//Save the specific settings
		saveWindowSettings(file);
		saveSoundSettings(file);

		file.close();
	}
	/////////////////////////////////////////////////
	bool Settings::loadWindowSettings()
	{
		std::fstream file;
		file.open("data/options.cfg", std::ios::in);

		if (file.is_open())
		{
			std::string line;
			while (std::getline(file, line))
			{
				if (line == "[window]")
				{
					//Next row = size, format: "width height"
					std::getline(file, line);
					std::stringstream sstr(line);
					sstr >> windowSettings.size.x >> windowSettings.size.y;
					//Next row = title
					std::getline(file, windowSettings.title);
					//Next row = style
					std::getline(file, line);
					sstr = std::stringstream(line);
					sstr >> windowSettings.style;
					//Next row = contextSettings format: "depth stencil antialiasing major minor"
					std::getline(file, line);
					sstr = std::stringstream(line);
					sstr >> windowSettings.settings.depthBits >> windowSettings.settings.stencilBits >>
						windowSettings.settings.antialiasingLevel >> windowSettings.settings.majorVersion >>
						windowSettings.settings.minorVersion;
					//Next row = vsync
					std::getline(file, line);
					sstr = std::stringstream(line);
					sstr >> windowSettings.vsync;
					//Next row = shaders
					std::getline(file, line);
					sstr = std::stringstream(line);
					sstr >> windowSettings.shaders;
					//Read everything
					file.close();
					return true;
				}
			}
		}

		return false;
	}
	/////////////////////////////////////////////////
	bool Settings::loadSoundSettings()
	{
		std::fstream file;
		file.open("data/options.cfg", std::ios::in);

		if (file.is_open())
		{
			std::string line;
			while (std::getline(file, line))
			{
				if (line == "[sound]")
				{
					//Next row = enabled
					std::getline(file, line);
					std::stringstream sstr(line);
					sstr >> soundSettings.enabled;
					//Next row = volumes format: "menu game"
					std::getline(file, line);
					sstr = std::stringstream(line);
					sstr >> soundSettings.volumeMusic >> soundSettings.volumeVFX;

					//Read everything
					file.close();
					return true;
				}
			}
		}
		return true;
	}
	/////////////////////////////////////////////////
	void Settings::saveWindowSettings(std::fstream &file)
	{
		file << "[window]\n";
		file << windowSettings.size.x << " " << windowSettings.size.y << "\n";
		file << windowSettings.title << "\n";
		file << windowSettings.style << "\n";
		file << windowSettings.settings.depthBits << " " << windowSettings.settings.stencilBits << " " <<
			windowSettings.settings.antialiasingLevel << " " << windowSettings.settings.majorVersion <<
			" " << windowSettings.settings.minorVersion << "\n";
		file << windowSettings.vsync << "\n";
		file << windowSettings.shaders << "\n";

		file << "\n";
	}
	/////////////////////////////////////////////////
	void Settings::saveSoundSettings(std::fstream &file)
	{
		file << "[sound]\n";
		file << soundSettings.enabled << "\n";
		file << soundSettings.volumeMusic << " " << soundSettings.volumeVFX << "\n";

		file << "\n";
	}
}