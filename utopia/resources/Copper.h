/*
 * Copper.h
 *
 *  Created on: 12.05.2015
 *      Author: Martin Ringwelski
 */

#ifndef RESOURCES_COPPER_H_
#define RESOURCES_COPPER_H_

#include "Resource.h"

class Copper: public Resource {
public:
	static const ResourceType_t TYPE = 5;

	Copper(unsigned int copper);
	virtual ~Copper();

	ResourceType_t getResourceType() {
		return TYPE;
	}

	unsigned int getCopper() const {
		return copper;
	}

	void setCopper(unsigned int copper) {
		this->copper = copper;
	}

	static bool loadMedia(SDL_Renderer* renderer);
	static void close();
	void renderFieldResource(SDL_Renderer* renderer, SDL_Rect rect);

private:
	unsigned int copper;
};

#endif /* RESOURCES_COPPER_H_ */
