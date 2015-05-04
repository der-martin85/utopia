/*
 * Field.cpp
 *
 *  Created on: 04.05.2015
 *      Author: jentin
 */

#include "Field.h"

Field::Field(): land(true) {
}

Field::~Field() {
	// TODO Auto-generated destructor stub
}

void Field::setType(bool land) {
	this->land = land;
}
bool Field::getType() {
	return land;
}

int Field::getTextureNumber() {
	if (land) {
		return 0;
	}
	return 4;
}
