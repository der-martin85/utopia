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
	resource(NULL),
	building(NULL),
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
void Field::setStone(unsigned int stone) {
	this->stone = stone;
}
void Field::setGold(unsigned int gold) {
	this->gold = gold;
}
void Field::setIron(unsigned int iron) {
	this->iron = iron;
}
void Field::setCopper(unsigned int copper) {
	this->copper = copper;
}
void Field::setCoal(unsigned int coal) {
	this->coal = coal;
}
void Field::setOil(unsigned int oil) {
	this->oil = oil;
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
unsigned int Field::getStone() const {
	return stone;
}
unsigned int Field::getGold() const {
	return gold;
}
unsigned int Field::getIron() const {
	return iron;
}
unsigned int Field::getCopper() const {
	return copper;
}
unsigned int Field::getCoal() const {
	return coal;
}
unsigned int Field::getOil() const {
	return oil;
}

