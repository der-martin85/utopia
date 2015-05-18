/*
 * Iron.h
 *
 *  Created on: 12.05.2015
 *      Author: Martin Ringwelski
 */

#ifndef RESOURCES_IRON_H_
#define RESOURCES_IRON_H_

#include "Resource.h"

class Iron: public Resource {
public:
	static const ResourceType_t TYPE = 4;
	static const int MAX_AMOUNT = 100;

	Iron(unsigned int iron);
	virtual ~Iron();

	ResourceType_t getResourceType() {
		return TYPE;
	}

	void writeResource(std::ofstream* file);

	void setAmount(unsigned int iron) {
		if (iron > MAX_AMOUNT) {
			iron = MAX_AMOUNT;
		}
		this->amount = iron;
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
			texture = &(ironTexture[numTexture - 1]);
		} else {
			texture = NULL;
		}
	}

	static const int NUM_TEXTURES = 3;
	static SDL_Texture* ironTexture[NUM_TEXTURES];
};

#endif /* RESOURCES_IRON_H_ */
