/*
 * Copper.cpp
 *
 *  Created on: 12.05.2015
 *      Author: Martin Ringwelski
 */

#include "Copper.h"

Copper::Copper(unsigned int copper):
	Resource::Resource(copper)
{
	// TODO Auto-generated constructor stub

}

Copper::~Copper() {
	// TODO Auto-generated destructor stub
}

bool Copper::loadMedia(SDL_Renderer* renderer) {
	bool success = true;
	SDL_Surface* tmp = NULL;

    return success;
}

void Copper::close() {

}

void Copper::renderFieldResource(SDL_Renderer* renderer, SDL_Rect rect) {

}
