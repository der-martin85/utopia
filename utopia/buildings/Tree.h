/*
 * Tree.h
 *
 *  Created on: 12.05.2015
 *      Author: Martin Ringwelski
 */

#ifndef RESOURCES_TREE_H_
#define RESOURCES_TREE_H_

#include "Building.h"
#include "SDL2/SDL.h"

class Tree: public Building {
public:
	static const BuildingType_t TYPE = 1;
	static const char MAX_NUM_TREES = 9;

	Tree(unsigned char numTrees);
	virtual ~Tree();

	BuildingType_t getBuildingType() {
		return TYPE;
	}

	void writeBuilding(std::ofstream* file);
	static Tree* loadTree(std::ifstream* file);

	unsigned char getNumTrees() const {
		return amount;
	}

	void setNumTrees(unsigned char num) {
		if (num > MAX_NUM_TREES) {
			num = MAX_NUM_TREES;
		}
		switch(kind) {
		case BROADLEAF:
			texture = &(broadleaf[num]);
			break;
		case CONIFER:
			texture = &(conifer[num]);
			break;
		case MIXED:
			texture = &(mixed[num]);
			break;
		}
		this->amount = num;
	}

	virtual void changeTime(int days);

	static bool loadMedia(SDL_Renderer* renderer);
	static void close();
	void setTexture();

private:
	static const unsigned int MAX_DAYS_GONE_BY = 365*100;

	enum forestKind {
		BROADLEAF,
		CONIFER,
		MIXED
	} kind;

	unsigned char amount;
	unsigned int daysGoneBy;

	static SDL_Texture* broadleaf[MAX_NUM_TREES];
	static SDL_Texture* conifer[MAX_NUM_TREES];
	static SDL_Texture* mixed[MAX_NUM_TREES];
};

#endif /* RESOURCES_TREE_H_ */
