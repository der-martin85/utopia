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
#include "buildings/Tree.h"

SDL_Texture* Field::sand		= NULL;
SDL_Texture* Field::gras		= NULL;
SDL_Texture* Field::water		= NULL;
SDL_Texture* Field::deepwater	= NULL;

Field::Field():
	land(true),
	moist(false),
	resource(NULL),
	building(NULL)
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

void Field::renderField(SDL_Renderer* renderer, SDL_Rect rect, int zoom, bool selected) const {
	if (selected) {
		SDL_SetTextureColorMod(sand, 128, 128, 255);
		SDL_SetTextureColorMod(gras, 128, 128, 255);
		SDL_SetTextureColorMod(water, 128, 255, 128);
		SDL_SetTextureColorMod(deepwater, 128, 255, 128);
	}
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
	if (selected) {
		SDL_SetTextureColorMod(sand, 255, 255, 255);
		SDL_SetTextureColorMod(gras, 255, 255, 255);
		SDL_SetTextureColorMod(water, 255, 255, 255);
		SDL_SetTextureColorMod(deepwater, 255, 255, 255);
	}
	if (getType() && resource != NULL) {
		resource->renderFieldResource(renderer, rect, zoom, selected);
	}
	if (building != NULL) {
		building->renderBuilding(renderer, rect, zoom, selected);
	}
}

void Field::writeFile(std::ofstream* fstream) {
	char data = 0;
	if (land) {
		data |= 0x80;
	}
	if (moist) {
		data |= 0x40;
	}
	if (resource != NULL) {
		data |= 0x08;
	}
	if (building != NULL) {
		data |= 0x04;
	}
	fstream->put(data);
	if (resource != NULL) {
		resource->writeResource(fstream);
	}
	if (building != NULL) {
		building->writeBuilding(fstream);
	}
}

void Field::readFile(std::ifstream* fstream) {
	char data;
	fstream->get(data);
	if (data & 0x80) {
		land = true;
	} else {
		land = false;
	}
	if (data & 0x40) {
		moist = true;
	} else {
		moist = false;
	}
	if (data & 0x08) {
		resource = Resource::loadResource(fstream);
	}
	if (data & 0x04) {
		building = Building::loadBuilding(fstream);
	}
}

Field::~Field() {
}

void Field::reset() {
	land = true;
	moist = false;

	if (resource != NULL) {
		delete resource;
		resource = NULL;
	}
	if (building != NULL) {
		delete building;
		building = NULL;
	}
}

void Field::setType(bool land) {
	this->land = land;
}
void Field::setMoist(bool moist) {
	this->moist = moist;
}
void Field::setTrees(unsigned int trees) {
	if (trees >= Tree::MAX_NUM_TREES) {
		trees = Tree::MAX_NUM_TREES - 1;
	} else {
		trees--;
	}
	if (building != NULL) {
		delete building;
	}
	building = new Tree(trees);
}
void Field::setStone(unsigned int stone) {
	if (stone > Stone::MAX_AMOUNT) {
		stone = Stone::MAX_AMOUNT;
	}
	if (resource != NULL) {
		delete resource;
	}
	resource = new Stone(stone);
}
void Field::setGold(unsigned int gold) {
	if (gold > Gold::MAX_AMOUNT) {
		gold = Gold::MAX_AMOUNT;
	}
	if (resource != NULL) {
		delete resource;
	}
	resource = new Gold(gold);
}
void Field::setIron(unsigned int iron) {
	if (iron > Iron::MAX_AMOUNT) {
		iron = Iron::MAX_AMOUNT;
	}
	if (resource != NULL) {
		delete resource;
	}
	resource = new Iron(iron);
}
void Field::setCopper(unsigned int copper) {
	if (copper > Copper::MAX_AMOUNT) {
		copper = Copper::MAX_AMOUNT;
	}
	if (resource != NULL) {
		delete resource;
	}
	resource = new Copper(copper);
}
void Field::setCoal(unsigned int coal) {
	if (coal > Coal::MAX_AMOUNT) {
		coal = Coal::MAX_AMOUNT;
	}
	if (resource != NULL) {
		delete resource;
	}
	resource = new Coal(coal);
}
void Field::setOil(unsigned int oil) {
	if (oil > Oil::MAX_AMOUNT) {
		oil = Oil::MAX_AMOUNT;
	}
	if (resource != NULL) {
		delete resource;
	}
	resource = new Oil(oil);
}

bool Field::getType() const {
	return land;
}
bool Field::getMoist() const {
	return moist;
}
unsigned int Field::getTrees() const {
	if (building != NULL && building->getBuildingType() == Tree::TYPE) {
		return ((Tree*)building)->getNumTrees();
	}
	return 0;
}
unsigned int Field::getStone() const {
	if (resource != NULL && resource->getResourceType() == Stone::TYPE) {
		return resource->getAmount();
	}
	return 0;
}
unsigned int Field::getGold() const {
	if (resource != NULL && resource->getResourceType() == Gold::TYPE) {
		return resource->getAmount();
	}
	return 0;
}
unsigned int Field::getIron() const {
	if (resource != NULL && resource->getResourceType() == Iron::TYPE) {
		return resource->getAmount();
	}
	return 0;
}
unsigned int Field::getCopper() const {
	if (resource != NULL && resource->getResourceType() == Copper::TYPE) {
		return resource->getAmount();
	}
	return 0;
}
unsigned int Field::getCoal() const {
	if (resource != NULL && resource->getResourceType() == Coal::TYPE) {
		return resource->getAmount();
	}
	return 0;
}
unsigned int Field::getOil() const {
	if (resource != NULL && resource->getResourceType() == Oil::TYPE) {
		return resource->getAmount();
	}
	return 0;
}

