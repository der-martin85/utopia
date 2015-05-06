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
bool Field::getType() const {
	return land;
}

int Field::getTextureNumber() const {
	if (land) {
		return 0;
	}
	return 4;
}
