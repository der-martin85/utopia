/*
 * Resource.h
 *
 *  Created on: 12.05.2015
 *      Author: Martin Ringwelski
 */

#ifndef RESOURCE_H_
#define RESOURCE_H_

#include "SDL2/SDL.h"
typedef int ResourceType_t;

class Resource {
public:
	Resource() {}
	virtual ~Resource() {}

	virtual void loadMedia(SDL_Renderer* renderer) = 0;
	virtual void close() = 0;
	virtual void renderFieldResource(SDL_Renderer* renderer, SDL_Rect rect) = 0;

	virtual ResourceType_t getResourceType() = 0;
};

#endif /* RESOURCE_H_ */
