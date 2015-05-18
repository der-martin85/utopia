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
	static const int MAX_AMOUNT = 100;

	Copper(unsigned int copper);
	virtual ~Copper();

	ResourceType_t getResourceType() {
		return TYPE;
	}

	void writeResource(std::ofstream* file);

	void setAmount(unsigned int copper) {
		if (copper > MAX_AMOUNT) {
			copper = MAX_AMOUNT;
		}
		this->amount = copper;
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
			texture = &(copperTexture[numTexture - 1]);
		} else {
			texture = NULL;
		}
	}

	static const int NUM_TEXTURES = 3;
	static SDL_Texture* copperTexture[NUM_TEXTURES];
};

#endif /* RESOURCES_COPPER_H_ */
