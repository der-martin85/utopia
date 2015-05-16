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
	static const int MAX_NUM_TREES = 9;

	Tree(unsigned int numTrees);
	virtual ~Tree();

	BuildingType_t getBuildingType() {
		return TYPE;
	}

	unsigned int getNumTrees() const {
		return amount;
	}

	void setNumTrees(unsigned int num) {
		amount = num;
	}

	void setAmount(unsigned int trees) {
		switch(kind) {
		case BROADLEAF:
			texture = &(broadleaf[trees]);
			break;
		case CONIFER:
			texture = &(conifer[trees]);
			break;
		case MIXED:
			texture = &(mixed[trees]);
			break;
		}
		this->amount = trees;
	}

	static bool loadMedia(SDL_Renderer* renderer);
	static void close();

private:
	enum forestKind {
		BROADLEAF,
		CONIFER,
		MIXED
	} kind;

	unsigned int amount;

	static SDL_Texture* broadleaf[MAX_NUM_TREES];
	static SDL_Texture* conifer[MAX_NUM_TREES];
	static SDL_Texture* mixed[MAX_NUM_TREES];
};

#endif /* RESOURCES_TREE_H_ */
