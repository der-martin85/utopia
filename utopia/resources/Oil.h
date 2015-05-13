/*
 * Oil.h
 *
 *  Created on: 12.05.2015
 *      Author: Martin Ringwelski
 */

#ifndef RESOURCES_OIL_H_
#define RESOURCES_OIL_H_

#include "Resource.h"

class Oil: public Resource {
public:
	static const ResourceType_t TYPE = 7;

	Oil(unsigned int oil);
	virtual ~Oil();

	ResourceType_t getResourceType() {
		return TYPE;
	}

	void setAmount(unsigned int oil) {
		this->amount = oil;
	}

	static bool loadMedia(SDL_Renderer* renderer);
	static void close();
	void renderFieldResource(SDL_Renderer* renderer, SDL_Rect rect);

private:
};

#endif /* RESOURCES_OIL_H_ */
