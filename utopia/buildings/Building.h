/*
 * Building.h
 *
 *  Created on: 12.05.2015
 *      Author: Martin Ringwelski
 */

#ifndef BUILDING_H_
#define BUILDING_H_

#include "SDL2/SDL.h"

class Building {
public:
	Building();
	virtual ~Building();

	virtual void loadMedia(SDL_Renderer* renderer) = 0;
	virtual void close() = 0;
	virtual void renderBuilding(SDL_Renderer* renderer, SDL_Rect rect);
};

#endif /* BUILDING_H_ */
