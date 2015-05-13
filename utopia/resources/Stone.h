/*
 * Stone.h
 *
 *  Created on: 12.05.2015
 *      Author: Martin Ringwelski
 */

#ifndef RESOURCES_STONE_H_
#define RESOURCES_STONE_H_

#include "Resource.h"

class Stone: public Resource {
public:
	static const ResourceType_t TYPE = 2;

	Stone(unsigned int stone);
	virtual ~Stone();

	ResourceType_t getResourceType() {
		return TYPE;
	}

	void setAmount(unsigned int stone) {
		this->amount = stone;
	}

	static bool loadMedia(SDL_Renderer* renderer);
	static void close();
	void renderFieldResource(SDL_Renderer* renderer, SDL_Rect rect);

private:
};

#endif /* RESOURCES_STONE_H_ */
