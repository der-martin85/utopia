/*
 * Menu.cpp
 *
 *  Created on: 09.05.2015
 *      Author: Martin Ringwelski
 */

#include "Menu.h"
#include "SDL2/SDL_image.h"

Menu::Menu(Settings* settings):
	quit(false),
	rt(NULL),
	settings(settings),
	entry(NULL)
{
	MenuEntry* tmp = new MenuEntry("./images/menu/landscape.png");
	entry = tmp;
	tmp = new MenuEntry("./images/menu/settings.png");
	tmp->addSubentry("./images/menu/settings.png");
	tmp->addSubentry("./images/menu/quit.png");
	entry->addEntry(tmp);
}

Menu::~Menu() {
	delete entry;
}

bool Menu::click(int x, int y, Uint8 button) {
	click_in clickon = entry->click(x, y,
			MenuEntry::ENTRY_SPACEX, MenuEntry::ENTRY_SPACEY,
			0, button);
	if (clickon.top == -1) {
		return false;
	} else {
		if (button == SDL_BUTTON_LEFT) {
			if (clickon.top == 1) {
				if (clickon.sub == 1) {
					quit = true;
				} else if (clickon.sub == 0) {
					settings->setShowSettings(true);
				}
			}
		}
		return true;
	}
}

void Menu::loadMedia(SDL_Renderer* renderer) {
	SDL_Surface* menuIMGs = IMG_Load("./images/menu/menu.png");
    menuBackgroundTexture = SDL_CreateTextureFromSurface(renderer, menuIMGs);
	SDL_FreeSurface(menuIMGs);

	entry->loadImages(renderer);

	settings->loadMedia(renderer);
}

void Menu::close() {
	SDL_DestroyTexture(menuBackgroundTexture);
	menuBackgroundTexture = NULL;

	entry->close();
}

void Menu::renderMenu(SDL_Renderer* renderer, int SCREEN_HEIGHT) {
	SDL_Rect dstrect = {0, 0, 100, SCREEN_HEIGHT};
	SDL_RenderCopy(renderer, menuBackgroundTexture, NULL, &dstrect);

	entry->renderMenu(renderer, MenuEntry::ENTRY_SPACEX, MenuEntry::ENTRY_SPACEY);

	if (settings->isShowSettings()) {
		settings->renderSettings(renderer);
	}
}
