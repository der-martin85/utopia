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

	Tree();
	virtual ~Tree();

	ResourceType_t getResourceType() {
		return TYPE;
	}

	unsigned int getTrees() const {
		return trees;
	}

	void setTrees(unsigned int trees) {
		this->trees = trees;
	}

private:
	unsigned int trees;
};

#endif /* RESOURCES_TREE_H_ */
