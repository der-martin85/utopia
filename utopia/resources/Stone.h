/*
 * Stone.h
 *
 *  Created on: 12.05.2015
 *      Author: Martin Ringwelski
 */

#ifndef RESOURCES_STONE_H_
#define RESOURCES_STONE_H_

#include "Resource.h"

class Stone: public Resource {
public:
	static const ResourceType_t TYPE = 2;

	Stone();
	virtual ~Stone();

	ResourceType_t getResourceType() {
		return TYPE;
	}

	unsigned int getStone() const {
		return stone;
	}

	void setStone(unsigned int stone) {
		this->stone = stone;
	}

private:
	unsigned int stone;
};

#endif /* RESOURCES_STONE_H_ */
