/*
 * Coal.cpp
 *
 *  Created on: 12.05.2015
 *      Author: Martin Ringwelski
 */

#include "Coal.h"
#include "SDL2/SDL_image.h"
#include <string>

SDL_Texture* Coal::coalTexture[Coal::NUM_TEXTURES] = {NULL, NULL, NULL};

Coal::Coal(unsigned int coal):
	Resource::Resource(coal)
{
	if (coal > MAX_AMOUNT) {
		coal = MAX_AMOUNT;
	}
	this->amount = coal;
	setTexture();
}

Coal::~Coal() {
}

bool Coal::loadMedia(SDL_Renderer* renderer) {
	bool success = true;
	SDL_Surface* tmp = NULL;

	std::string stoneName = "./images/resources/coal/coal";

	for (int i = 0; i < NUM_TEXTURES; i++) {
		std::string name = stoneName + std::to_string(i) + ".png";
		tmp = IMG_Load(name.c_str());
		coalTexture[i] = SDL_CreateTextureFromSurface(renderer, tmp);
		SDL_FreeSurface(tmp);
	}

    return success;
}

void Coal::close() {
	for (int i = 0; i < NUM_TEXTURES; i++) {
		SDL_DestroyTexture(coalTexture[i]);
		coalTexture[i] = NULL;
	}
}

