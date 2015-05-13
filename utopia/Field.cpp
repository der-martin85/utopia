/*
 * Field.cpp
 *
 *  Created on: 04.05.2015
 *      Author: Martin Ringwelski
 */

#include "Field.h"
#include "SDL2/SDL_image.h"

#include "resources/Coal.h"
#include "resources/Copper.h"
#include "resources/Gold.h"
#include "resources/Iron.h"
#include "resources/Oil.h"
#include "resources/Stone.h"
#include "resources/Tree.h"

SDL_Texture* Field::sand		= NULL;
SDL_Texture* Field::gras		= NULL;
SDL_Texture* Field::water	= NULL;
SDL_Texture* Field::deepwater = NULL;

Field::Field():
	land(true),
	moist(false),
	resource(NULL),
	building(NULL),
	stone(0),
	gold(0),
	iron(0),
	copper(0),
	coal(0),
	oil(0)
{
}

bool Field::loadMedia(SDL_Renderer* renderer) {
	bool success = true;
	SDL_Surface* tmp = NULL;

	tmp = IMG_Load("./images/landscape/sand.png");
	sand = SDL_CreateTextureFromSurface(renderer, tmp);
	SDL_FreeSurface(tmp);

	tmp = IMG_Load("./images/landscape/gras.png");
	gras = SDL_CreateTextureFromSurface(renderer, tmp);
	SDL_FreeSurface(tmp);

	tmp = IMG_Load("./images/landscape/water0.png");
	water = SDL_CreateTextureFromSurface(renderer, tmp);
	SDL_FreeSurface(tmp);

	tmp = IMG_Load("./images/landscape/water1.png");
	deepwater = SDL_CreateTextureFromSurface(renderer, tmp);
	SDL_FreeSurface(tmp);

	success = success && Coal::loadMedia(renderer);
	success = success && Copper::loadMedia(renderer);
	success = success && Gold::loadMedia(renderer);
	success = success && Iron::loadMedia(renderer);
	success = success && Oil::loadMedia(renderer);
	success = success && Stone::loadMedia(renderer);
	success = success && Tree::loadMedia(renderer);

    return success;
}

void Field::close() {
	SDL_DestroyTexture(sand);
	sand = NULL;

	SDL_DestroyTexture(gras);
	gras = NULL;

	SDL_DestroyTexture(water);
	water = NULL;

	SDL_DestroyTexture(deepwater);
	deepwater = NULL;

	Coal::close();
	Copper::close();
	Gold::close();
	Iron::close();
	Oil::close();
	Stone::close();
	Tree::close();
}

void Field::renderField(SDL_Renderer* renderer, SDL_Rect rect, int zoom) const {
	if (getType()) {
		if (getMoist()) {
			   SDL_RenderCopy(renderer, gras, NULL, &rect);
		} else {
			   SDL_RenderCopy(renderer, sand, NULL, &rect);
		}
	} else {
		if (getMoist()) {
			   SDL_RenderCopy(renderer, deepwater, NULL, &rect);
		} else {
			   SDL_RenderCopy(renderer, water, NULL, &rect);
		}
	}
	if (resource != NULL) {
		resource->renderFieldResource(renderer, rect);
	}
}

Field::~Field() {
}

void Field::reset() {
	land = true;
	moist = false;
	stone = 0;
	gold = 0;
	iron = 0;
	copper = 0;
	coal = 0;
	oil = 0;

	if (resource != NULL) {
		delete resource;
	}
}

void Field::setType(bool land) {
	this->land = land;
}
void Field::setMoist(bool moist) {
	this->moist = moist;
}
void Field::setTrees(unsigned int trees) {
	if (trees > Tree::MAX_NUM_TREES) {
		trees = Tree::MAX_NUM_TREES - 1;
	} else {
		trees--;
	}
	if (resource != NULL) {
		delete resource;
	}
	resource = new Tree(trees);
}
void Field::setStone(unsigned int stone) {
	this->stone = stone;
}
void Field::setGold(unsigned int gold) {
	this->gold = gold;
}
void Field::setIron(unsigned int iron) {
	this->iron = iron;
}
void Field::setCopper(unsigned int copper) {
	this->copper = copper;
}
void Field::setCoal(unsigned int coal) {
	this->coal = coal;
}
void Field::setOil(unsigned int oil) {
	this->oil = oil;
}

bool Field::getType() const {
	return land;
}
bool Field::getMoist() const {
	return moist;
}
unsigned int Field::getTrees() const {
	if (resource != NULL && resource->getResourceType() == Tree::TYPE) {
		return resource->getAmount();
	}
	return 0;
}
unsigned int Field::getStone() const {
	return stone;
}
unsigned int Field::getGold() const {
	return gold;
}
unsigned int Field::getIron() const {
	return iron;
}
unsigned int Field::getCopper() const {
	return copper;
}
unsigned int Field::getCoal() const {
	return coal;
}
unsigned int Field::getOil() const {
	return oil;
}

