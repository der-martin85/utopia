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
	Resource(unsigned int amount): amount(amount), texture(NULL) {}
	virtual ~Resource() {}

	void renderFieldResource(SDL_Renderer* renderer, SDL_Rect rect) const {
		if (texture != NULL && *texture != NULL) {
			SDL_RenderCopy(renderer, *texture, NULL, &rect);
		}
	}
	virtual void setAmount(unsigned int amount) = 0;
	unsigned int getAmount() const {
		return amount;
	}

	virtual ResourceType_t getResourceType() = 0;

protected:
	unsigned int amount;
	SDL_Texture** texture;
};

#endif /* RESOURCE_H_ */
