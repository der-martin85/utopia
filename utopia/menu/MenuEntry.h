/*
 * MenuEntry.h
 *
 *  Created on: 10.05.2015
 *      Author: Martin Ringwelski
 */

#ifndef MENUENTRY_H_
#define MENUENTRY_H_

#include "SDL2/SDL.h"
#include <string>

struct click_in {
	int top;
	int sub;
};

class SubMenuEntry {
public:
	SubMenuEntry(std::string imageFile);
	virtual ~SubMenuEntry();

	void loadImages(SDL_Renderer* renderer);
	void renderMenu(SDL_Renderer* renderer, int x, int y);
	void close();

	void addEntry(std::string imgFile);

	int click(int x, int y, int startx, int starty, int num, Uint8 button);
private:
	std::string		imageFile;
	SDL_Texture*	texture;

	SubMenuEntry*	nextEntry;
};

class MenuEntry {
public:
	static const int ENTRY_HEIGHT	= 50;
	static const int ENTRY_WIDTH	= 80;
	static const int ENTRY_SPACEX	= 10;
	static const int ENTRY_SPACEY	= 10;

	MenuEntry(std::string imageFile);
	virtual ~MenuEntry();

	void loadImages(SDL_Renderer* renderer);
	void renderMenu(SDL_Renderer* renderer, int x, int y);
	void close();

	void addEntry(MenuEntry* entry);
	void addSubentry(std::string imgFile);

	click_in click(int x, int y, int startx, int starty, int num, Uint8 button);
private:
	std::string		imageFile;
	SDL_Texture*	texture;

	bool			showSubmenu;

	MenuEntry*		nextEntry;
	SubMenuEntry*	submenu;
};

#endif /* MENUENTRY_H_ */
