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
	static const int MAX_AMOUNT = 100;

	Coal(unsigned int coal);
	virtual ~Coal();

	ResourceType_t getResourceType() {
		return TYPE;
	}

	void setAmount(unsigned int coal) {
		if (coal > MAX_AMOUNT) {
			coal = MAX_AMOUNT;
		}
		this->amount = coal;
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
			texture = &(coalTexture[numTexture - 1]);
		} else {
			texture = NULL;
		}
	}

	static const int NUM_TEXTURES = 3;
	static SDL_Texture* coalTexture[NUM_TEXTURES];
};

#endif /* RESOURCES_COAL_H_ */
