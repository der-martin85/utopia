/*
 * Settings.h
 *
 *  Created on: 14.05.2015
 *      Author: Martin Ringwelski
 */

#ifndef MENU_SETTINGS_H_
#define MENU_SETTINGS_H_

#include "SDL2/SDL.h"
#include <boost/filesystem.hpp>

class Settings {
public:
	Settings(bool fullscreen = false, bool backgroundMusic = true, int screenWidth = 800, int screenHeight = 600);
	virtual ~Settings();

	void loadSettings();
	void saveSettings();

	bool loadMedia(SDL_Renderer* renderer);
	void close();
	void renderSettings(SDL_Renderer* renderer);

	bool isBackgroundMusic() const {
		return backgroundMusic;
	}

	void setBackgroundMusic(bool backgroundMusic) {
		this->backgroundMusic = backgroundMusic;
	}

	bool isFullscreen() const {
		return fullscreen;
	}

	void setFullscreen(bool fullscreen) {
		this->fullscreen = fullscreen;
	}

	int getScreenHeight() const {
		return screenHeight;
	}

	void setScreenHeight(int screenHeight) {
		this->screenHeight = screenHeight;
	}

	int getScreenWidth() const {
		return screenWidth;
	}

	void setScreenWidth(int screenWidth) {
		this->screenWidth = screenWidth;
	}

private:
	static boost::filesystem::path configFile;

	bool fullscreen;
	bool backgroundMusic;
	int screenWidth;
	int screenHeight;
};

#endif /* MENU_SETTINGS_H_ */
