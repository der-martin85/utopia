/*
 * Resource.h
 *
 *  Created on: 12.05.2015
 *      Author: Martin Ringwelski
 */

#ifndef RESOURCE_H_
#define RESOURCE_H_

#include "SDL2/SDL.h"
#include <fstream>
typedef int ResourceType_t;

class Resource {
public:
	Resource(unsigned int amount): amount(amount), texture(NULL) {}
	virtual ~Resource() {}

	void renderFieldResource(SDL_Renderer* renderer, SDL_Rect rect, int zoom, bool selected) const {
		if (texture != NULL && *texture != NULL) {
			if (selected) {
				SDL_SetTextureColorMod(*texture, 128, 128, 255);
			}
			SDL_RenderCopy(renderer, *texture, NULL, &rect);
			if (selected) {
				SDL_SetTextureColorMod(*texture, 255, 255, 255);
			}
		}
	}
	virtual void setAmount(unsigned int amount) = 0;
	unsigned int getAmount() const {
		return amount;
	}
	virtual ResourceType_t getResourceType() = 0;
	virtual void writeResource(std::ofstream* file) = 0;
	static Resource* loadResource(std::ifstream* file);

protected:
	unsigned int amount;
	SDL_Texture** texture;
};

#endif /* RESOURCE_H_ */
