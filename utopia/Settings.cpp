/*
 * Settings.cpp
 *
 *  Created on: 14.05.2015
 *      Author: Martin Ringwelski
 */

#include "Settings.h"
#include <fstream>

boost::filesystem::path Settings::ConfigFile = boost::filesystem::path("./config.ini");
SDL_Color Settings::TextColor = {0, 0, 0};
TTF_Font* Settings::Font = NULL;

Settings::Settings(bool fullscreen, bool backgroundMusic, int screenWidth, int screenHeight):
		showSettings(false),
		fullscreen(fullscreen),
		backgroundMusic(backgroundMusic),
		resolution(R1024X768),
		videoLabel(NULL),
		fullscreenCheckbox(NULL),
		r1024x768RadioButton(NULL),
		r1280x720RadioButton(NULL),
		r1280x800RadioButton(NULL),
		r1920x1080RadioButton(NULL),
		r1920x1200RadioButton(NULL),
		audioLabel(NULL),
		musicCheckbox(NULL),
		okButton(NULL)
{
}

Settings::~Settings() {
}

bool Settings::loadMedia(SDL_Renderer* renderer) {
	Font = TTF_OpenFont("FreeSans.ttf", 24);
	if (Font == NULL) {
		return false;
	}
	int XStart = (getScreenWidth() - swWidth) / 2;
	int YStart = (getScreenHeight() - swHeight) / 2;
	int YPos = YStart + 10;
	videoLabel = new Label("Video Settings", Font, TextColor,
			XStart + 10, YPos);
	YPos += videoLabel->getRect().h + 5;
	fullscreenCheckbox = new Checkbox(&fullscreen, "Fullscreen", Font, TextColor,
			XStart + 10, YPos);
	YPos += fullscreenCheckbox->getHeigth() + 10;
	r1024x768RadioButton = new RadioButton((int*)(&resolution), (int)(R1024X768), "1024 x 768", Font, TextColor,
			XStart + 10, YPos);
	YPos += r1024x768RadioButton->getHeigth() + 5;
	r1280x720RadioButton = new RadioButton((int*)(&resolution), (int)(R1280X720), "1280 x 720", Font, TextColor,
			XStart + 10, YPos);
	YPos += r1280x720RadioButton->getHeigth() + 5;
	r1280x800RadioButton = new RadioButton((int*)(&resolution), (int)(R1280X800), "1280 x 800", Font, TextColor,
			XStart + 10, YPos);
	YPos += r1280x800RadioButton->getHeigth() + 5;
	r1920x1080RadioButton = new RadioButton((int*)(&resolution), (int)(R1920X1080), "1920 x 1080", Font, TextColor,
			XStart + 10, YPos);
	YPos += r1920x1080RadioButton->getHeigth() + 5;
	r1920x1200RadioButton = new RadioButton((int*)(&resolution), (int)(R1920X1200), "1920 x 1200", Font, TextColor,
			XStart + 10, YPos);

	YPos += r1920x1200RadioButton->getHeigth() + 10;
	audioLabel = new Label("Audio Settings", Font, TextColor,
			XStart + 10, YPos);
	YPos = audioLabel->getRect().y + audioLabel->getRect().h + 5;
	musicCheckbox = new Checkbox(&backgroundMusic, "Background Music", Font, TextColor,
			XStart + 10, YPos);

	okButton = new Button("Ok", Font, TextColor,
			XStart + swWidth - 110, YStart + swHeight - 50, 100, 40);

	return true;
}

void Settings::loadSettings() {
	if (boost::filesystem::exists(ConfigFile) &&
			boost::filesystem::is_regular_file(ConfigFile))
	{
		std::ifstream cFile;
		cFile.open(ConfigFile.c_str());
		int res;
		cFile >> res >> fullscreen >> backgroundMusic;
		resolution = (Resolution_t) res;
		cFile.close();
	}
}

void Settings::saveSettings() {
	std::ofstream cFile;
	cFile.open(ConfigFile.c_str());
	cFile << resolution << std::endl;
	cFile << fullscreen << std::endl;
	cFile << backgroundMusic << std::endl;
	cFile.close();
}

void Settings::close() {
	delete videoLabel;
	delete fullscreenCheckbox;
	delete r1024x768RadioButton;
	delete r1280x720RadioButton;
	delete r1280x800RadioButton;
	delete r1920x1080RadioButton;
	delete r1920x1200RadioButton;
	delete audioLabel;
	delete musicCheckbox;
	delete okButton;
}

SDL_Rect renderRadioButton(SDL_Renderer* renderer, bool checked, const char* text, TTF_Font* font, SDL_Color& color, int posX, int posY) {
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text, color);

	SDL_Rect Message_rect = {
			posX,
			posY,
			0,
			0
	};
	TTF_SizeText(font, text, &(Message_rect.w), &(Message_rect.h));

	const int boxSize = Message_rect.h - 6;
	Message_rect.x += Message_rect.h;

	SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
	SDL_Rect box = {
			posX + 3,
			posY + 3,
			boxSize,
			boxSize
	};
	SDL_RenderFillRect( renderer, &box );
	if (checked) {
		SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
		SDL_Rect check = {
				posX + 6,
				posY + 6,
				boxSize - 6,
				boxSize - 6
		};
		SDL_RenderFillRect( renderer, &check );
	}

	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

	return box;
}

void Settings::renderSettings(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor( renderer, 192, 192, 192, 255 );

	int XStart = (getScreenWidth() - swWidth) / 2;
	int YStart = (getScreenHeight() - swHeight) / 2;

	SDL_Rect window = {
			XStart,
			YStart,
			swWidth,
			swHeight
	};
	SDL_RenderFillRect( renderer, &window );

	videoLabel->render(renderer);
	fullscreenCheckbox->render(renderer);
	r1024x768RadioButton->render(renderer);
	r1280x720RadioButton->render(renderer);
	r1280x800RadioButton->render(renderer);
	r1920x1080RadioButton->render(renderer);
	r1920x1200RadioButton->render(renderer);
	audioLabel->render(renderer);
	musicCheckbox->render(renderer);
	okButton->render(renderer);
}

bool Settings::click(int x, int y, Uint8 button) {
	int XStart = (getScreenWidth() - swWidth) / 2;
	int YStart = (getScreenHeight() - swHeight) / 2;

	if (x >= XStart && x < XStart + swWidth) {
		if (y >= YStart && y < YStart + swHeight) {
			if (fullscreenCheckbox->checkClick(x, y)) {
				fullscreen = !fullscreen;
			}
			if (r1024x768RadioButton->checkClick(x, y)) {
				resolution = R1024X768;
			} else if (r1280x720RadioButton->checkClick(x, y)) {
				resolution = R1280X720;
			} else if (r1280x800RadioButton->checkClick(x, y)) {
				resolution = R1280X800;
			} else if (r1920x1080RadioButton->checkClick(x, y)) {
				resolution = R1920X1080;
			} else if (r1920x1200RadioButton->checkClick(x, y)) {
				resolution = R1920X1200;
			}
			setPositions();
			if (musicCheckbox->checkClick(x, y)) {
				backgroundMusic = !backgroundMusic;
			}
			if (okButton->checkClick(x, y)) {
				showSettings = false;
			}
			return true;
		}
	}
	return false;
}

void Settings::setPositions() {
	int XStart = (getScreenWidth() - swWidth) / 2;
	int YStart = (getScreenHeight() - swHeight) / 2;

	int YPos = YStart + 10;
	videoLabel->setPos(XStart + 10, YPos);
	YPos += videoLabel->getRect().h + 5;
	fullscreenCheckbox->setPos(XStart + 10, YPos);
	YPos += fullscreenCheckbox->getHeigth() + 10;
	r1024x768RadioButton->setPos(XStart + 10, YPos);
	YPos += r1024x768RadioButton->getHeigth() + 5;
	r1280x720RadioButton->setPos(XStart + 10, YPos);
	YPos += r1280x720RadioButton->getHeigth() + 5;
	r1280x800RadioButton->setPos(XStart + 10, YPos);
	YPos += r1280x800RadioButton->getHeigth() + 5;
	r1920x1080RadioButton->setPos(XStart + 10, YPos);
	YPos += r1920x1080RadioButton->getHeigth() + 5;
	r1920x1200RadioButton->setPos(XStart + 10, YPos);

	YPos += r1920x1200RadioButton->getHeigth() + 10;
	audioLabel->setPos(XStart + 10, YPos);
	YPos = audioLabel->getRect().y + audioLabel->getRect().h + 5;
	musicCheckbox->setPos(XStart + 10, YPos);

	okButton->setPos(XStart + swWidth - 110, YStart + swHeight - 50);
}
