/*
 * Resource.cpp
 *
 *  Created on: 18.05.2015
 *      Author: Martin Ringwelski
 */


#include "Coal.h"
#include "Copper.h"
#include "Gold.h"
#include "Iron.h"
#include "Oil.h"
#include "Stone.h"

Resource* Resource::loadResource(std::ifstream* file) {
	Resource* ret = NULL;
	char c;
	int type = 0;
	file->get(c);
	type = ((unsigned int)c) << 8;
	file->get(c);
	type |= ((unsigned char)c);
	file->get(c);
	switch (type) {
	case Coal::TYPE:
		ret = new Coal(((unsigned int)c));
		break;
	case Copper::TYPE:
		ret = new Copper(((unsigned int)c));
		break;
	case Gold::TYPE:
		ret = new Gold(((unsigned int)c));
		break;
	case Iron::TYPE:
		ret = new Iron(((unsigned int)c));
		break;
	case Oil::TYPE:
		ret = new Oil(((unsigned int)c));
		break;
	case Stone::TYPE:
		ret = new Stone(((unsigned int)c));
		break;
	}
	return ret;
}
