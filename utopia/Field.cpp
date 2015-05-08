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

void Field::reset() {
	land = true;
	moist = false;
	trees = 0;
	stone = 0;
	gold = 0;
	iron = 0;
	copper = 0;
	coal = 0;
	oil = 0;
}

void Field::setType(bool land) {
	this->land = land;
}
void Field::setMoist(bool moist) {
	this->moist = moist;
}
void Field::setTrees(unsigned int trees) {
	this->trees = trees;
}

bool Field::getType() const {
	return land;
}
bool Field::getMoist() const {
	return moist;
}
unsigned int Field::getTrees() const {
	return trees;
}

