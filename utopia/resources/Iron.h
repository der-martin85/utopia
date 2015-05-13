/*
 * Iron.h
 *
 *  Created on: 12.05.2015
 *      Author: Martin Ringwelski
 */

#ifndef RESOURCES_IRON_H_
#define RESOURCES_IRON_H_

#include "Resource.h"

class Iron: public Resource {
public:
	static const ResourceType_t TYPE = 4;

	Iron(unsigned int iron);
	virtual ~Iron();

	ResourceType_t getResourceType() {
		return TYPE;
	}

	void setAmount(unsigned int iron) {
		this->amount = iron;
	}

	static bool loadMedia(SDL_Renderer* renderer);
	static void close();
	void renderFieldResource(SDL_Renderer* renderer, SDL_Rect rect);

private:
};

#endif /* RESOURCES_IRON_H_ */
