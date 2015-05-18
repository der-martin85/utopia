/*
 * Tree.cpp
 *
 *  Created on: 12.05.2015
 *      Author: Martin Ringwelski
 */

#include "Tree.h"
#include "SDL2/SDL_image.h"
#include <string>

SDL_Texture* Tree::broadleaf[Tree::MAX_NUM_TREES] = {NULL, NULL, NULL, NULL, NULL};
SDL_Texture* Tree::conifer[Tree::MAX_NUM_TREES] = {NULL, NULL, NULL, NULL, NULL};
SDL_Texture* Tree::mixed[Tree::MAX_NUM_TREES] = {NULL, NULL, NULL, NULL, NULL};

Tree::Tree(unsigned char numTrees):
	amount(numTrees)
{
	switch(rand()%3) {
	case 0:
		kind = BROADLEAF;
		break;
	case 1:
		kind = CONIFER;
		break;
	case 2:
		kind = MIXED;
		break;
	}
	switch(kind) {
	case BROADLEAF:
		texture = &(broadleaf[numTrees]);
		break;
	case CONIFER:
		texture = &(conifer[numTrees]);
		break;
	case MIXED:
		texture = &(mixed[numTrees]);
		break;
	}
}

Tree::~Tree() {
}

bool Tree::loadMedia(SDL_Renderer* renderer) {
	bool success = true;
	SDL_Surface* tmp = NULL;

	std::string broadleafName = "./images/buildings/trees/broadleaf";
	std::string coniferName = "./images/buildings/trees/conifer";
	std::string mixedName = "./images/buildings/trees/mixed";

	for (int i = 0; i < MAX_NUM_TREES; i++) {
		std::string name = broadleafName + std::to_string(i) + ".png";
		tmp = IMG_Load(name.c_str());
		broadleaf[i] = SDL_CreateTextureFromSurface(renderer, tmp);
		SDL_FreeSurface(tmp);

		name = coniferName + std::to_string(i) + ".png";
		tmp = IMG_Load(name.c_str());
		conifer[i] = SDL_CreateTextureFromSurface(renderer, tmp);
		SDL_FreeSurface(tmp);

		name = mixedName + std::to_string(i) + ".png";
		tmp = IMG_Load(name.c_str());
		mixed[i] = SDL_CreateTextureFromSurface(renderer, tmp);
		SDL_FreeSurface(tmp);
	}

    return success;
}

void Tree::close() {
	for (int i = 0; i < MAX_NUM_TREES; i++) {
		SDL_DestroyTexture(broadleaf[i]);
		broadleaf[i] = NULL;

		SDL_DestroyTexture(conifer[i]);
		conifer[i] = NULL;

		SDL_DestroyTexture(mixed[i]);
		mixed[i] = NULL;
	}
}

void Tree::writeBuilding(std::ofstream* file) {
	file->put((char)(TYPE >> 8));
	file->put((char)(TYPE));
	file->put((char)kind);
	file->put((char)amount);
}

Tree* Tree::loadTree(std::ifstream* file) {
	Tree* ret = new Tree(0);

	char kind, amount;

	file->get(kind);
	file->get(amount);

	ret->kind = (forestKind)kind;
	ret->amount = (unsigned char)amount;

	return ret;
}
