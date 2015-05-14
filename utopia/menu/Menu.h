/*
 * Menu.h
 *
 *  Created on: 09.05.2015
 *      Author: Martin Ringwelski
 */

#ifndef MENU_H_
#define MENU_H_

class RenderThread;
#include "../RenderThread.h"
#include "SDL2/SDL.h"
#include "MenuEntry.h"

class Menu {
public:
	Menu();
	virtual ~Menu();

	void setRenderThread(RenderThread* rt) {
		this->rt = rt;
	}
	bool click(int x, int y, Uint8 button);
	void loadMedia(SDL_Renderer* renderer);
	void close();
	void renderMenu(SDL_Renderer* renderer, int SCREEN_HEIGHT);

	bool quit;
private:
	RenderThread* rt;

	SDL_Texture* menuBackgroundTexture = NULL;

	MenuEntry* entry;
};

#endif /* MENU_H_ */
