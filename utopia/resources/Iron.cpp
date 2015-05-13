/*
 * Iron.cpp
 *
 *  Created on: 12.05.2015
 *      Author: Martin Ringwelski
 */

#include "Iron.h"

Iron::Iron(unsigned int iron):
	Resource::Resource(iron)
{
	// TODO Auto-generated constructor stub

}

Iron::~Iron() {
	// TODO Auto-generated destructor stub
}

bool Iron::loadMedia(SDL_Renderer* renderer) {
	bool success = true;
	SDL_Surface* tmp = NULL;

    return success;
}

void Iron::close() {

}

void Iron::renderFieldResource(SDL_Renderer* renderer, SDL_Rect rect) {

}

