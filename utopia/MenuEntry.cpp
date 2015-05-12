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

	if (submenu != NULL) {
		submenu->loadImages(renderer);
	}
	if (nextEntry != NULL) {
		nextEntry->loadImages(renderer);
	}
}

void MenuEntry::close() {
	SDL_DestroyTexture(texture);
	texture = NULL;
}

void MenuEntry::renderMenu(SDL_Renderer* renderer, int x, int y) {
	SDL_Rect dstrect = {x, y, ENTRY_WIDTH, ENTRY_HEIGHT};
	SDL_RenderCopy(renderer, texture, NULL, &dstrect);

	if (showSubmenu && submenu != NULL) {
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
		if (submenu != NULL && showSubmenu) {
			ret.sub = submenu->click(x, y,
					(startx + ENTRY_WIDTH + ENTRY_SPACEX), starty,
					0, button);
		}
		if (ret.sub == -1 && nextEntry != NULL) {
			ret = nextEntry->click(x, y,
					startx, (starty + ENTRY_HEIGHT + ENTRY_SPACEY),
					num + 1, button);
		} else if (ret.sub != -1) {
			ret.top = num;
		}
	}
	return ret;
}

void MenuEntry::addEntry(MenuEntry* entry) {
	if (nextEntry != NULL) {
		nextEntry->addEntry(entry);
	} else {
		nextEntry = entry;
	}
}

void MenuEntry::addSubentry(std::string imgFile) {
	if (submenu != NULL) {
		submenu->addEntry(imgFile);
	} else {
		submenu = new SubMenuEntry(imgFile);
	}
}

SubMenuEntry::SubMenuEntry(std::string imageFile):
	imageFile(imageFile),
	texture(NULL),
	nextEntry(NULL)
{
}

SubMenuEntry::~SubMenuEntry() {
	if (nextEntry != NULL) {
		delete nextEntry;
	}
}

void SubMenuEntry::loadImages(SDL_Renderer* renderer) {
	SDL_Surface* img = IMG_Load(imageFile.c_str());
    texture = SDL_CreateTextureFromSurface(renderer, img);
	SDL_FreeSurface(img);

	if (nextEntry != NULL) {
		nextEntry->loadImages(renderer);
	}
}

void SubMenuEntry::close() {
	SDL_DestroyTexture(texture);
	texture = NULL;
}

void SubMenuEntry::renderMenu(SDL_Renderer* renderer, int x, int y) {
	SDL_Rect dstrect = {x, y, MenuEntry::ENTRY_WIDTH, MenuEntry::ENTRY_HEIGHT};
	SDL_RenderCopy(renderer, texture, NULL, &dstrect);

	if (nextEntry != NULL) {
		nextEntry->renderMenu(renderer, x, (y + MenuEntry::ENTRY_HEIGHT + MenuEntry::ENTRY_SPACEY));
	}
}

int SubMenuEntry::click(int x, int y, int startx, int starty, int num, Uint8 button) {
	int ret = -1;
	if ((x > startx && x < (startx + MenuEntry::ENTRY_WIDTH)) &&
			(y > starty && y < (starty + MenuEntry::ENTRY_HEIGHT))) {
		ret = num;
	} else {
		if (nextEntry != NULL) {
			ret = nextEntry->click(x, y,
					startx, (starty + MenuEntry::ENTRY_HEIGHT + MenuEntry::ENTRY_SPACEY),
					num + 1, button);
		}
	}
	return ret;
}

void SubMenuEntry::addEntry(std::string imgFile) {
	if (nextEntry != NULL) {
		nextEntry->addEntry(imgFile);
	} else {
		nextEntry = new SubMenuEntry(imgFile);
	}
}
