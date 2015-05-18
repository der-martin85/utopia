/*
 * Iron.cpp
 *
 *  Created on: 12.05.2015
 *      Author: Martin Ringwelski
 */

#include "Iron.h"
#include "SDL2/SDL_image.h"
#include <string>

SDL_Texture* Iron::ironTexture[Iron::NUM_TEXTURES] = {NULL, NULL, NULL};

Iron::Iron(unsigned int iron):
	Resource::Resource(iron)
{
	if (iron > MAX_AMOUNT) {
		iron = MAX_AMOUNT;
	}
	this->amount = iron;
	setTexture();
}

Iron::~Iron() {
	// TODO Auto-generated destructor stub
}

bool Iron::loadMedia(SDL_Renderer* renderer) {
	bool success = true;
	SDL_Surface* tmp = NULL;

	std::string stoneName = "./images/resources/iron/iron";

	for (int i = 0; i < NUM_TEXTURES; i++) {
		std::string name = stoneName + std::to_string(i) + ".png";
		tmp = IMG_Load(name.c_str());
		ironTexture[i] = SDL_CreateTextureFromSurface(renderer, tmp);
		SDL_FreeSurface(tmp);
	}

    return success;
}

void Iron::writeResource(std::ofstream* file) {
	file->put((char)(TYPE >> 8));
	file->put((char)(TYPE));
	file->put((char)amount);
}

void Iron::close() {
	for (int i = 0; i < NUM_TEXTURES; i++) {
		SDL_DestroyTexture(ironTexture[i]);
		ironTexture[i] = NULL;
	}
}

