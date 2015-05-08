/*
 * Field.cpp
 *
 *  Created on: 04.05.2015
 *      Author: Martin Ringwelski
 */

#include "Field.h"

Field::Field():
	land(true),
	moist(false),
	trees(0),
	stone(0),
	gold(0),
	iron(0),
	copper(0),
	coal(0),
	oil(0)
{
}

Field::~Field() {
}

void Field::setType(bool land) {
	this->land = land;
}
bool Field::getType() const {
	return land;
}

int Field::getTextureNumber() const {
	if (land) {
		if (moist) {
			return 1;
		} else {
			return 0;
		}
	} else if (moist) {
		return 5;
	}
	return 4;
}
