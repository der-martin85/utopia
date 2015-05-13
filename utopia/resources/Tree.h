/*
 * Tree.h
 *
 *  Created on: 12.05.2015
 *      Author: Martin Ringwelski
 */

#ifndef RESOURCES_TREE_H_
#define RESOURCES_TREE_H_

#include "Resource.h"

class Tree: public Resource {
public:
	static const ResourceType_t TYPE = 1;
	static const int MAX_NUM_TREES = 9;

	Tree(unsigned int numTrees);
	virtual ~Tree();

	ResourceType_t getResourceType() {
		return TYPE;
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

	static SDL_Texture* broadleaf[MAX_NUM_TREES];
	static SDL_Texture* conifer[MAX_NUM_TREES];
	static SDL_Texture* mixed[MAX_NUM_TREES];
};

#endif /* RESOURCES_TREE_H_ */
