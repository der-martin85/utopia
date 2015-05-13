/*
 * Stone.cpp
 *
 *  Created on: 12.05.2015
 *      Author: Martin Ringwelski
 */

#include "Stone.h"
#include "SDL2/SDL_image.h"
#include <string>

SDL_Texture* Stone::stoneTexture[Stone::NUM_TEXTURES] = {NULL, NULL, NULL};

Stone::Stone(unsigned int stone):
	Resource::Resource(stone)
{
	if (stone > MAX_AMOUNT) {
		stone = MAX_AMOUNT;
	}
	this->amount = stone;
	setTexture();
}

Stone::~Stone() {
	// TODO Auto-generated destructor stub
}

bool Stone::loadMedia(SDL_Renderer* renderer) {
	bool success = true;
	SDL_Surface* tmp = NULL;

	std::string stoneName = "./images/resources/stone/stone";

	for (int i = 0; i < NUM_TEXTURES; i++) {
		std::string name = stoneName + std::to_string(i) + ".png";
		tmp = IMG_Load(name.c_str());
		stoneTexture[i] = SDL_CreateTextureFromSurface(renderer, tmp);
		SDL_FreeSurface(tmp);
	}

    return success;
}

void Stone::close() {
	for (int i = 0; i < NUM_TEXTURES; i++) {
		SDL_DestroyTexture(stoneTexture[i]);
		stoneTexture[i] = NULL;
	}
}

