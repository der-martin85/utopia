/*
 * Oil.cpp
 *
 *  Created on: 12.05.2015
 *      Author: Martin Ringwelski
 */

#include "Oil.h"
#include "SDL2/SDL_image.h"
#include <string>

SDL_Texture* Oil::oilTexture[Oil::NUM_TEXTURES] = {NULL, NULL, NULL};

Oil::Oil(unsigned int coal):
	Resource::Resource(coal)
{
	if (coal > MAX_AMOUNT) {
		coal = MAX_AMOUNT;
	}
	this->amount = coal;
	setTexture();
}

Oil::~Oil() {
}

bool Oil::loadMedia(SDL_Renderer* renderer) {
	bool success = true;
	SDL_Surface* tmp = NULL;

	std::string stoneName = "./images/resources/oil/oil";

	for (int i = 0; i < NUM_TEXTURES; i++) {
		std::string name = stoneName + std::to_string(i) + ".png";
		tmp = IMG_Load(name.c_str());
		oilTexture[i] = SDL_CreateTextureFromSurface(renderer, tmp);
		SDL_FreeSurface(tmp);
	}

    return success;
}

void Oil::writeResource(std::ofstream* file) {
	file->put((char)(TYPE >> 8));
	file->put((char)(TYPE));
	file->put((char)amount);
}

void Oil::close() {
	for (int i = 0; i < NUM_TEXTURES; i++) {
		SDL_DestroyTexture(oilTexture[i]);
		oilTexture[i] = NULL;
	}
}
