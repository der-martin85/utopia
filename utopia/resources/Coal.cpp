/*
 * Coal.cpp
 *
 *  Created on: 12.05.2015
 *      Author: Martin Ringwelski
 */

#include "Coal.h"

Coal::Coal(unsigned int coal):
	Resource::Resource(coal)
{
	// TODO Auto-generated constructor stub
}

Coal::~Coal() {
	// TODO Auto-generated destructor stub
}

bool Coal::loadMedia(SDL_Renderer* renderer) {
	bool success = true;
	SDL_Surface* tmp = NULL;

    return success;
}

void Coal::close() {

}

void Coal::renderFieldResource(SDL_Renderer* renderer, SDL_Rect rect) {

}
