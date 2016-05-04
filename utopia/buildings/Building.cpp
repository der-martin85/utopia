/*
 * Building.cpp
 *
 *  Created on: 18.05.2015
 *      Author: Martin Ringwelski
 */

#include "Tree.h"

Building* Building::loadBuilding(std::ifstream* file) {
	Building* ret = NULL;

	char c;
	int type = 0;
	file->get(c);
	type = ((unsigned int)c) << 8;
	file->get(c);
	type |= ((unsigned int)c);

	switch (type) {
	case Tree::TYPE:
		ret = Tree::loadTree(file);
		break;
	}

	return ret;
}

void Building::changeTime(int days) {
}
