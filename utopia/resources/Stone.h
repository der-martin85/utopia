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
	static const int MAX_AMOUNT = 100;

	Stone(unsigned int stone);
	virtual ~Stone();

	ResourceType_t getResourceType() {
		return TYPE;
	}

	void setAmount(unsigned int stone) {
		if (stone > MAX_AMOUNT) {
			stone = MAX_AMOUNT;
		}
		this->amount = stone;
		setTexture();
	}

	static bool loadMedia(SDL_Renderer* renderer);
	static void close();

private:
	void setTexture() {
		int numTexture = (amount * (NUM_TEXTURES + 1)) / (MAX_AMOUNT - (MAX_AMOUNT / NUM_TEXTURES + 1));
		if (numTexture > 0) {
			numTexture--;
			if (numTexture > NUM_TEXTURES) {
				numTexture = NUM_TEXTURES - 1;
			}
			texture = &(stoneTexture[numTexture - 1]);
		} else {
			texture = NULL;
		}
	}

	static const int NUM_TEXTURES = 3;
	static SDL_Texture* stoneTexture[NUM_TEXTURES];
};

#endif /* RESOURCES_STONE_H_ */
