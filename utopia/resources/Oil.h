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
	static const int MAX_AMOUNT = 100;

	Oil(unsigned int oil);
	virtual ~Oil();

	ResourceType_t getResourceType() {
		return TYPE;
	}

	void writeResource(std::ofstream* file);

	void setAmount(unsigned int oil) {
		if (oil > MAX_AMOUNT) {
			oil = MAX_AMOUNT;
		}
		this->amount = oil;
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
			texture = &(oilTexture[numTexture - 1]);
		} else {
			texture = NULL;
		}
	}

	static const int NUM_TEXTURES = 3;
	static SDL_Texture* oilTexture[NUM_TEXTURES];
};

#endif /* RESOURCES_OIL_H_ */
