/*
 * Copper.cpp
 *
 *  Created on: 12.05.2015
 *      Author: Martin Ringwelski
 */

#include "Copper.h"
#include "SDL2/SDL_image.h"
#include <string>

SDL_Texture* Copper::copperTexture[Copper::NUM_TEXTURES] = {NULL, NULL, NULL};

Copper::Copper(unsigned int copper):
	Resource::Resource(copper)
{
	if (copper > MAX_AMOUNT) {
		copper = MAX_AMOUNT;
	}
	this->amount = copper;
	setTexture();
}

Copper::~Copper() {
}

bool Copper::loadMedia(SDL_Renderer* renderer) {
	bool success = true;
	SDL_Surface* tmp = NULL;

	std::string stoneName = "./images/resources/copper/copper";

	for (int i = 0; i < NUM_TEXTURES; i++) {
		std::string name = stoneName + std::to_string(i) + ".png";
		tmp = IMG_Load(name.c_str());
		copperTexture[i] = SDL_CreateTextureFromSurface(renderer, tmp);
		SDL_FreeSurface(tmp);
	}

    return success;
}

void Copper::close() {
	for (int i = 0; i < NUM_TEXTURES; i++) {
		SDL_DestroyTexture(copperTexture[i]);
		copperTexture[i] = NULL;
	}
}

