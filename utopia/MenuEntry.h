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

class MenuEntry {
public:
	MenuEntry();
	virtual ~MenuEntry();
private:
	std::string		imageFile;
	SDL_Texture*	texture;

};

#endif /* MENUENTRY_H_ */
