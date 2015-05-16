/*
 * Settings.h
 *
 *  Created on: 14.05.2015
 *      Author: Martin Ringwelski
 */

#ifndef MENU_SETTINGS_H_
#define MENU_SETTINGS_H_

#include <SDL2/SDL.h>
#include <boost/filesystem.hpp>
#include <SDL2/SDL_ttf.h>
#include "gui/Label.h"
#include "gui/Button.h"
#include "gui/Checkbox.h"
#include "gui/RadioButton.h"

class Settings {
public:
	typedef enum {
		R1024X768 = 0,
		R1280X720 = 1,
		R1280X800 = 2,
		R1920X1080 = 3,
		R1920X1200 = 4
	} Resolution_t;

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

	bool click(int x, int y, Uint8 button);

	int getScreenHeight() const {
		switch (resolution) {
		case R1024X768:
			return 768;
			break;
		case R1280X720:
			return 720;
			break;
		case R1280X800:
			return 800;
			break;
		case R1920X1080:
			return 1080;
			break;
		case R1920X1200:
			return 1200;
			break;
		}
		return 0;
	}

	void setResolution(Resolution_t res) {
		this->resolution = res;
	}
	Resolution_t getResolution() {
		return resolution;
	}

	int getScreenWidth() const {
		switch (resolution) {
		case R1024X768:
			return 1024;
			break;
		case R1280X720:
			return 1280;
			break;
		case R1280X800:
			return 1280;
			break;
		case R1920X1080:
			return 1920;
			break;
		case R1920X1200:
			return 1920;
			break;
		}
		return 0;
	}

	bool isShowSettings() const {
		return showSettings;
	}

	void setShowSettings(bool showSettings) {
		this->showSettings = showSettings;
	}

private:
	void setPositions();

	static boost::filesystem::path ConfigFile;
	static TTF_Font *Font;
	static SDL_Color TextColor;

	static const int swHeight = 400;
	static const int swWidth = 600;

	bool showSettings;

	bool fullscreen;
	bool backgroundMusic;
	Resolution_t resolution;

	Label* videoLabel;
	Checkbox* fullscreenCheckbox;
	RadioButton* r1024x768RadioButton;
	RadioButton* r1280x720RadioButton;
	RadioButton* r1280x800RadioButton;
	RadioButton* r1920x1080RadioButton;
	RadioButton* r1920x1200RadioButton;
	Label* audioLabel;
	Checkbox* musicCheckbox;
	Button* okButton;
};

#endif /* MENU_SETTINGS_H_ */
