/*
 * MenuEntry.cpp
 *
 *  Created on: 10.05.2015
 *      Author: Martin Ringwelski
 */

#include "MenuEntry.h"
#include "SDL2/SDL_image.h"

MenuEntry::MenuEntry(std::string imageFile):
	imageFile(imageFile),
	texture(NULL),
	showSubmenu(false),
	nextEntry(NULL),
	submenu(NULL)
{
}

MenuEntry::~MenuEntry() {
	if (nextEntry != NULL) {
		delete nextEntry;
	}
}

void MenuEntry::loadImages(SDL_Renderer* renderer) {
	SDL_Surface* img = IMG_Load(imageFile.c_str());
    texture = SDL_CreateTextureFromSurface(renderer, img);
	SDL_FreeSurface(img);
}

void MenuEntry::close() {
	SDL_DestroyTexture(texture);
	texture = NULL;
}

void MenuEntry::renderMenu(SDL_Renderer* renderer, int x, int y) {
	SDL_Rect dstrect = {x, y, ENTRY_WIDTH, ENTRY_HEIGHT};
	SDL_RenderCopy(renderer, texture, NULL, &dstrect);

	if (showSubmenu) {
		submenu->renderMenu(renderer, (x + ENTRY_WIDTH + ENTRY_SPACEX), y);
	}

	if (nextEntry != NULL) {
		nextEntry->renderMenu(renderer, x, (y + ENTRY_HEIGHT + ENTRY_SPACEY));
	}
}

click_in MenuEntry::click(int x, int y, int startx, int starty, int num, Uint8 button) {
	click_in ret = {-1, -1};
	if ((x > startx && x < (startx + ENTRY_WIDTH)) &&
			(y > starty && y < (starty + ENTRY_HEIGHT))) {
		ret.top = num;
		showSubmenu = !showSubmenu;
	} else {
		if (submenu != NULL) {
			ret = submenu->click(x, y,
					(startx + ENTRY_WIDTH + ENTRY_SPACEX), starty,
					0, button);
		}
		if (ret.top == -1 && nextEntry != NULL) {
			ret = nextEntry->click(x, y,
					startx, (starty + ENTRY_HEIGHT + ENTRY_SPACEY),
					num + 1, button);
		} else if (ret.top != -1) {
			ret.sub = ret.top;
			ret.top = num;
		}
	}
	return ret;
}

void MenuEntry::addEntry(std::string imgFile) {
	if (nextEntry != NULL) {
		nextEntry->addEntry(imgFile);
	} else {
		nextEntry = new MenuEntry(imgFile);
	}
}

void MenuEntry::addSubentry(std::string imgFile) {
	if (submenu != NULL) {
		submenu->addEntry(imgFile);
	} else {
		submenu = new MenuEntry(imgFile);
	}
}
