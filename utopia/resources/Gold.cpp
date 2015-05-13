/*
 * Gold.cpp
 *
 *  Created on: 12.05.2015
 *      Author: Martin Ringwelski
 */

#include "Gold.h"

Gold::Gold(unsigned int gold):
	Resource::Resource(gold)
{
	// TODO Auto-generated constructor stub

}

Gold::~Gold() {
	// TODO Auto-generated destructor stub
}

bool Gold::loadMedia(SDL_Renderer* renderer) {
	bool success = true;
	SDL_Surface* tmp = NULL;

    return success;
}

void Gold::close() {

}

void Gold::renderFieldResource(SDL_Renderer* renderer, SDL_Rect rect) {

}
