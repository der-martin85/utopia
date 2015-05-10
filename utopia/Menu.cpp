/*
 * Menu.cpp
 *
 *  Created on: 09.05.2015
 *      Author: Martin Ringwelski
 */

#include "Menu.h"
#include "SDL2/SDL_image.h"

Menu::Menu():
	quit(false),
	mX(0), mY(0),
	rt(NULL)
{
}

Menu::~Menu() {
}

void Menu::click() {
	if (mX > 10 && mX < 90) {
		if (mY > 10 && mY < 60) {
			quit = true;
		}
	}
}

void Menu::loadMedia(SDL_Renderer* renderer) {
	SDL_Surface* menuIMGs = IMG_Load("./images/menu.png");
    menuBackgroundTexture = SDL_CreateTextureFromSurface(renderer, menuIMGs);
	SDL_FreeSurface(menuIMGs);
    menuIMGs = IMG_Load("./images/menu-settings.png");
    menuSettingsTexture = SDL_CreateTextureFromSurface(renderer, menuIMGs);
	SDL_FreeSurface(menuIMGs);
}

void Menu::close() {
	SDL_DestroyTexture(menuBackgroundTexture);
	menuBackgroundTexture = NULL;
	SDL_DestroyTexture(menuSettingsTexture);
	menuSettingsTexture = NULL;

}

void Menu::renderMenu(SDL_Renderer* renderer, int SCREEN_HEIGHT) {
	SDL_Rect dstrect = {0, 0, 100, SCREEN_HEIGHT};
	SDL_RenderCopy(renderer, menuBackgroundTexture, NULL, &dstrect);

	dstrect = {10, 10, 80, 50};
	SDL_RenderCopy(renderer, menuSettingsTexture, NULL, &dstrect);
}
