/*
 * Settings.cpp
 *
 *  Created on: 14.05.2015
 *      Author: Martin Ringwelski
 */

#include "Settings.h"
#include <fstream>

boost::filesystem::path Settings::configFile = boost::filesystem::path("./config.ini");

Settings::Settings(bool fullscreen, bool backgroundMusic, int screenWidth, int screenHeight):
	fullscreen(fullscreen),
	backgroundMusic(backgroundMusic),
	screenWidth(screenWidth),
	screenHeight(screenHeight)
{
}

Settings::~Settings() {
}

bool Settings::loadMedia(SDL_Renderer* renderer) {
	return true;
}

void Settings::loadSettings() {
	if (boost::filesystem::exists(configFile) &&
			boost::filesystem::is_regular_file(configFile))
	{
		std::ifstream cFile;
		cFile.open(configFile.c_str());
		cFile >> screenWidth >> screenHeight >> fullscreen >> backgroundMusic;
		cFile.close();
	}
}

void Settings::saveSettings() {
	std::ofstream cFile;
	cFile.open(configFile.c_str());
	cFile << screenWidth << std::endl;
	cFile << screenHeight << std::endl;
	cFile << fullscreen << std::endl;
	cFile << backgroundMusic << std::endl;
	cFile.close();
}

void Settings::close() {
}

void Settings::renderSettings(SDL_Renderer* renderer) {
}
