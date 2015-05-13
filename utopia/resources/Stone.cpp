/*
 * Stone.cpp
 *
 *  Created on: 12.05.2015
 *      Author: Martin Ringwelski
 */

#include "Stone.h"

Stone::Stone(unsigned int stone):
	Resource::Resource(stone)
{
	// TODO Auto-generated constructor stub

}

Stone::~Stone() {
	// TODO Auto-generated destructor stub
}

bool Stone::loadMedia(SDL_Renderer* renderer) {
	bool success = true;
	SDL_Surface* tmp = NULL;

    return success;
}

void Stone::close() {

}

void Stone::renderFieldResource(SDL_Renderer* renderer, SDL_Rect rect) {

}

