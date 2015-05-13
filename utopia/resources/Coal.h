/*
 * Coal.h
 *
 *  Created on: 12.05.2015
 *      Author: Martin Ringwelski
 */

#ifndef RESOURCES_COAL_H_
#define RESOURCES_COAL_H_

#include "Resource.h"

class Coal: public Resource {
public:
	static const ResourceType_t TYPE = 6;

	Coal(unsigned int coal);
	virtual ~Coal();

	virtual ResourceType_t getResourceType() {
		return TYPE;
	}

	void setAmount(unsigned int coal) {
		this->amount = coal;
	}

	static bool loadMedia(SDL_Renderer* renderer);
	static void close();
	void renderFieldResource(SDL_Renderer* renderer, SDL_Rect rect);

private:
};

#endif /* RESOURCES_COAL_H_ */
