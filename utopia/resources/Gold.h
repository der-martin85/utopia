/*
 * Gold.h
 *
 *  Created on: 12.05.2015
 *      Author: Martin Ringwelski
 */

#ifndef RESOURCES_GOLD_H_
#define RESOURCES_GOLD_H_

#include "Resource.h"

class Gold: public Resource {
public:
	static const ResourceType_t TYPE = 3;

	Gold(unsigned int gold);
	virtual ~Gold();

	ResourceType_t getResourceType() {
		return TYPE;
	}

	void setAmount(unsigned int gold) {
		this->amount = gold;
	}

	static bool loadMedia(SDL_Renderer* renderer);
	static void close();
	void renderFieldResource(SDL_Renderer* renderer, SDL_Rect rect);

private:
};

#endif /* RESOURCES_GOLD_H_ */
