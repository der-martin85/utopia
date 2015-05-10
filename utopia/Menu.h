/*
 * Menu.h
 *
 *  Created on: 09.05.2015
 *      Author: Martin Ringwelski
 */

#ifndef MENU_H_
#define MENU_H_

class RenderThread;
#include "RenderThread.h"
#include "SDL2/SDL.h"

class Menu {
public:
	Menu();
	virtual ~Menu();

	void setMouseState(int mX, int mY) {
		this->mX = mX;
		this->mY = mY;
	}
	void setRenderThread(RenderThread* rt) {
		this->rt = rt;
	}
	void click();
	void loadMedia(SDL_Renderer* renderer);
	void close();
	void renderMenu(SDL_Renderer* renderer, int SCREEN_HEIGHT);

	bool quit;
private:
	int mX, mY;
	RenderThread* rt;

	SDL_Texture* menuBackgroundTexture = NULL;
	SDL_Texture* menuSettingsTexture = NULL;
};

#endif /* MENU_H_ */
