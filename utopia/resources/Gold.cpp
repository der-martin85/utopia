/*
 * Gold.cpp
 *
 *  Created on: 12.05.2015
 *      Author: Martin Ringwelski
 */

#include "Gold.h"

#include "SDL2/SDL_image.h"
#include <string>

SDL_Texture* Gold::goldTexture[Gold::NUM_TEXTURES] = {NULL, NULL, NULL};

Gold::Gold(unsigned int gold):
	Resource::Resource(gold)
{
	if (gold > MAX_AMOUNT) {
		gold = MAX_AMOUNT;
	}
	this->amount = gold;
	setTexture();
}

Gold::~Gold() {
}

bool Gold::loadMedia(SDL_Renderer* renderer) {
	bool success = true;
	SDL_Surface* tmp = NULL;

	std::string stoneName = "./images/resources/gold/gold";

	for (int i = 0; i < NUM_TEXTURES; i++) {
		std::string name = stoneName + std::to_string(i) + ".png";
		tmp = IMG_Load(name.c_str());
		goldTexture[i] = SDL_CreateTextureFromSurface(renderer, tmp);
		SDL_FreeSurface(tmp);
	}

    return success;
}

void Gold::close() {
	for (int i = 0; i < NUM_TEXTURES; i++) {
		SDL_DestroyTexture(goldTexture[i]);
		goldTexture[i] = NULL;
	}
}

