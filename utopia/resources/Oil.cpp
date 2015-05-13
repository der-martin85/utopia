/*
 * Oil.cpp
 *
 *  Created on: 12.05.2015
 *      Author: Martin Ringwelski
 */

#include "Oil.h"

Oil::Oil(unsigned int oil):
	Resource::Resource(oil)
{
	// TODO Auto-generated constructor stub

}

Oil::~Oil() {
	// TODO Auto-generated destructor stub
}

bool Oil::loadMedia(SDL_Renderer* renderer) {
	bool success = true;
	SDL_Surface* tmp = NULL;

    return success;
}

void Oil::close() {

}

void Oil::renderFieldResource(SDL_Renderer* renderer, SDL_Rect rect) {

}

