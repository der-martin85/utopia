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
	static const int MAX_AMOUNT = 100;

	Gold(unsigned int gold);
	virtual ~Gold();

	ResourceType_t getResourceType() {
		return TYPE;
	}

	void writeResource(std::ofstream* file);

	void setAmount(unsigned int gold) {
		if (gold > MAX_AMOUNT) {
			gold = MAX_AMOUNT;
		}
		this->amount = gold;
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
			texture = &(goldTexture[numTexture - 1]);
		} else {
			texture = NULL;
		}
	}

	static const int NUM_TEXTURES = 3;
	static SDL_Texture* goldTexture[NUM_TEXTURES];
};

#endif /* RESOURCES_GOLD_H_ */
